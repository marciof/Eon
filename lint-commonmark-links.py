#!/usr/bin/env python3
# -*- coding: UTF-8 -*-

# Standard:
import fileinput
from http import HTTPStatus
from html.parser import HTMLParser
import logging
import queue
import sys
import threading
from typing import Callable, Iterable
from urllib.error import URLError, HTTPError
from urllib.request import Request, urlopen

# External:
# TODO use the official lib https://github.com/commonmark/cmark
# TODO paka.cmark fails to build on Windows https://github.com/PavloKapyshin/paka.cmark/pull/6
from commonmark import commonmark


formatter = logging.Formatter('%(asctime)s [%(levelname)s] %(message)s')
stream_handler = logging.StreamHandler(sys.stderr)
stream_handler.setFormatter(formatter)

# TODO log to stdout or stderr depending on level?
logger = logging.getLogger(__name__)
logger.setLevel(logging.INFO)
logger.addHandler(stream_handler)


# TODO logging
class LinkExtractorHtmlParser (HTMLParser):
    def __init__(self, callback: Callable[[str], None]):
        super().__init__()
        self.callback = callback

    def handle_starttag(self, tag: str, attrs) -> None:
        if tag == 'a':
            for (attr_name, attr_value) in attrs:
                if attr_name == 'href':
                    self.callback(attr_value)


# TODO stream input
def slurp_input() -> str:
    return ''.join([line for line in fileinput.input()])


# TODO walk CommonMark AST instead of parsing to HTML just to get links
def convert_commonmark_to_html(text: str) -> str:
    return commonmark(text)


def list_html_links(html: str, callback: Callable[[str], None]) -> None:
    link_extractor = LinkExtractorHtmlParser(callback)
    link_extractor.feed(html)


# TODO report redirects?
def is_link_valid(link: str) -> bool:
    if not link.startswith('http'):
        return True

    try:
        with urlopen(Request(link, method = 'HEAD')) as request:
            status_code = request.getcode()
            print(status_code, link)
            return status_code == HTTPStatus.OK
    except HTTPError as error:
        print(error.code, link)
        logger.exception('%s: %s', link, error)
        return False
    except URLError as error:
        print('?', link)
        logger.exception('%s: %s', link, error)
        return False


class DeDupQueue (queue.Queue):
    def __init__(self):
        super().__init__()
        self.seen_hashes = set()


    def put(self, item, **kwargs):
        item_hash = hash(item)

        if item_hash not in self.seen_hashes:
            self.seen_hashes.add(item_hash)
            super().put(item, **kwargs)


# TODO normalize links?
# TODO cache results?
def validate_links(
        commonmark_doc_iterator: Iterable[str],
        max_num_parallel_workers: int = 10) -> bool:

    link_queue = DeDupQueue()
    are_links_valid = True

    def validate_link_queue() -> None:
        nonlocal are_links_valid

        while True:
            if not is_link_valid(link_queue.get()):
                are_links_valid = False

            link_queue.task_done()

    for i in range(max_num_parallel_workers):
        threading.Thread(target = validate_link_queue, daemon = True).start()

    for commonmark_doc in commonmark_doc_iterator:
        list_html_links(convert_commonmark_to_html(commonmark_doc),
            callback = link_queue.put)

    link_queue.join()
    return are_links_valid


# TODO documentation
# TODO tests
if __name__ == '__main__':
    if not validate_links(commonmark_doc for commonmark_doc in [slurp_input()]):
        sys.exit(1)
