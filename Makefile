.POSIX:

PYTHON=python3

all: lint-documentation lint-sources

# TODO validate CommonMark documents
# TODO spellcheck documents and source code documentation
lint-documentation: COPYRIGHT.md LICENSE.md README.md
	$(PYTHON) tools/lint-commonmark-links.py $?

# TODO lint other sources (eg. config files, C files, Makefiles, etc)
# TODO lint coding style
# TODO validate links in source code
lint-sources: lint-sources-python

# TODO move to tools/Makefile
lint-sources-python: tools/lint-commonmark-links.py
	$(PYTHON) -m mypy $?
	$(PYTHON) -m pycodestyle $?
