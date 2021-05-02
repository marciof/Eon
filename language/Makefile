.POSIX:

PYTHON=python3

all: lint-documentation

# TODO validate links in org-mode files
# TODO validate CommonMark documents
# TODO avoid duplicate work linting links (eg. documents at root)
lint-documentation: language.md
	$(PYTHON) ../tools/lint-commonmark-links.py $?
