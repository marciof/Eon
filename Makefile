.POSIX:

PYTHON=python3

all: lint-documentation

# TODO validate links in sources
# TODO lint Python (Mypy, pycodestyle)
lint-documentation: COPYRIGHT.md LICENSE.md README.md
	$(PYTHON) lint-commonmark-links.py $?
