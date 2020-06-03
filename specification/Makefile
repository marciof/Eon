.POSIX:

PYTHON=python3

all: lint

lint: language.md
	$(PYTHON) validate-commonmark-links.py $?
