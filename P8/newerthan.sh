#!/bin/bash

echo -n "Enter file 1: "
read file1

echo -n "Enter file 2: "
read file2

if [ $file1 -nt $file2 ]; then
    echo "Newest file is file 1."
elif [ $file2 -nt $file1 ]; then
    echo "Newest file is file 2."
else
    echo "Neither file is newer."
fi
