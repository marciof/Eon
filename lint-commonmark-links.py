#!/usr/bin/env python3
# -*- coding: UTF-8 -*-

"""
Validate links in CommonMark documents are valid and respond with HTTP 200 OK.

Arguments: see Python's `fileinput.input()`
Stdin: see Python's `fileinput.input()`
Stdout: CSV with one line per unique link, containing the HTTP status code
        (or '?' if unknown) followed by the URL
"""

# stdlib
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

# external
# TODO use the official lib https://github.com/commonmark/cmark
# TODO paka.cmark fails to build on Windows
#      https://github.com/PavloKapyshin/paka.cmark/pull/6
# TODO missing type stubs for some external libraries
from commonmark import commonmark  # type: ignore


def create_logger() -> logging.Logger:
    formatter = logging.Formatter('%(asctime)s [%(levelname)s] %(message)s')
    stream_handler = logging.StreamHandler(sys.stderr)
    stream_handler.setFormatter(formatter)

    # TODO log to stdout or stderr depending on level?
    logger = logging.getLogger(__name__)
    logger.setLevel(logging.INFO)
    logger.addHandler(stream_handler)

    return logger


class LinkExtractorHtmlParser (HTMLParser):
    """
    HTML parser that extracts `href`'s and supplies them to a callback.
    """

    def __init__(self, callback: Callable[[str], None]):
        super().__init__()
        self.callback = callback

    def handle_starttag(self, tag: str, attrs) -> None:
        if tag == 'a':
            for (attr_name, attr_value) in attrs:
                if attr_name == 'href':
                    self.callback(attr_value)


# TODO stream input for performance? (measure first)
# TODO split inputs per filename for debugging?
def slurp_input() -> str:
    return ''.join([line for line in fileinput.input()])


# TODO walk CommonMark AST, instead of parsing to HTML just to get links
def convert_commonmark_to_html(text: str) -> str:
    return commonmark(text)


def list_html_links(html: str, callback: Callable[[str], None]) -> None:
    link_extractor = LinkExtractorHtmlParser(callback)
    link_extractor.feed(html)


# TODO report redirects?
# TODO ensure valid CSV output
# TODO use logger instead of `print`ing
def is_link_valid(link: str, logger: logging.Logger) -> bool:
    if not link.startswith('http'):
        return True

    try:
        with urlopen(Request(link, method='HEAD')) as request:
            status_code = request.getcode()
            print('%d,%s' % (status_code, link))
            return status_code == HTTPStatus.OK
    except HTTPError as error:
        print('%d,%s' % (error.code, link))
        logger.exception('%s: %s', link, error)
        return False
    except URLError as error:
        print('?,%s' % link)
        logger.exception('%s: %s', link, error)
        return False


class DedupingQueue (queue.Queue):
    """
    Queue that discards items previously seen.
    """

    def __init__(self):
        super().__init__()
        self.seen_items = set()

    def put(self, item, **kwargs):
        if item not in self.seen_items:
            self.seen_items.add(item)
            super().put(item, **kwargs)


# TODO thread count was chosen arbitrarily
def validate_links(
        commonmark_doc_iterator: Iterable[str],
        logger: logging.Logger,
        max_num_parallel_workers: int = 10) -> bool:

    link_queue = DedupingQueue()
    are_links_valid = True

    def validate_link_queue() -> None:
        nonlocal are_links_valid

        while True:
            if not is_link_valid(link_queue.get(), logger):
                are_links_valid = False

            link_queue.task_done()

    for i in range(max_num_parallel_workers):
        threading.Thread(target=validate_link_queue, daemon=True).start()

    for commonmark_doc in commonmark_doc_iterator:
        list_html_links(convert_commonmark_to_html(commonmark_doc),
                        callback=link_queue.put)

    link_queue.join()
    return are_links_valid


# TODO tests
if __name__ == '__main__':
    if not validate_links((doc for doc in [slurp_input()]), create_logger()):
        sys.exit(1)
