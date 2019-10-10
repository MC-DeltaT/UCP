#/bin/bash

if [ -r $1 ]; then
    echo "File is readable."
fi

if [ -w $1 ]; then
    echo "File is writable."
fi

if [ -x $1 ]; then
    echo "File is executable."
fi
