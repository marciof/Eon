.POSIX:

PYTHON=python3

all: lint-documentation lint-sources

# TODO validate links in sources
# TODO validate CommonMark documents
lint-documentation: COPYRIGHT.md LICENSE.md README.md
	$(PYTHON) lint-commonmark-links.py $?

# TODO lint other sources (eg. Travis YAML config file)
lint-sources: lint-sources-python

lint-sources-python: lint-commonmark-links.py
	$(PYTHON) -m mypy $?
	$(PYTHON) -m pycodestyle $?
