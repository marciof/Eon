.POSIX:

PYTHON=python3

all: lint-documentation

lint-documentation: README.md LICENSE.md specification/language.md
	$(PYTHON) lint-commonmark-links.py $?
