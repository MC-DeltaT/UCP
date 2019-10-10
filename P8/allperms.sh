#!/bin/bash

for file in `find -type f`; do
    echo -n "$file | "
    if [ -r $file ]; then
        echo -n "r"
    fi
    if [ -w $file ]; then
        echo -n "w"
    fi
    if [ -x $file ]; then
        echo -n "x"
    fi
    echo
done
