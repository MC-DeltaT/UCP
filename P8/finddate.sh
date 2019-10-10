#!/bin/bash

files=`find -type f`
day=`date +%d`

for file in $files; do
    if [[ $file == *$day* ]]; then
        echo "$file"
    fi
done
