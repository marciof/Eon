.POSIX:

PYTHON=python3

all: lint-documentation

# TODO validate links in org-mode files
lint-documentation: language.md
	$(PYTHON) ../lint-commonmark-links.py $?
