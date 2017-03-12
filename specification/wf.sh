#!/bin/sh
# word frequency

sed -E 's/[^[:alpha:]]+/\n/g' \    # split into lines on non-alpha runs
    | grep -vE '^$' \              # remove empty lines
    | tr '[:upper:]' '[:lower:]' \ # convert to lower case
    | sort \                       # sort words
    | uniq -c \                    # count unique words
    | sort -nr \                   # sort by descending frequency
    | head -n "${1:-10}"           # print top most frequent
