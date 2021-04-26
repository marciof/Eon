.POSIX:

PYTHON=python3

all: lint-documentation

# TODO validate links in org-mode files
# TODO validate CommonMark documents
lint-documentation: language.md
	$(PYTHON) ../lint-commonmark-links.py $?
