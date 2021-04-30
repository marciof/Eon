.POSIX:

PYTHON=python3

all: lint-documentation lint-sources

# TODO validate CommonMark documents
# TODO spellcheck documents and source code documentation
lint-documentation: COPYRIGHT.md LICENSE.md README.md
	$(PYTHON) lint-commonmark-links.py $?

# TODO lint other sources (eg. config files, C files, etc)
# TODO lint coding style
# TODO validate links in source code
lint-sources: lint-sources-python

lint-sources-python: lint-commonmark-links.py
	$(PYTHON) -m mypy $?
	$(PYTHON) -m pycodestyle $?
