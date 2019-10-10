#/bin/bash

files=`find -type f`
for file1 in $files; do
    for file2 in $files; do
        if [ $file1 != $file2 ]; then
            if cmp -s $file1 $file2; then
                echo "$file1 and $file2"
            fi
        fi
    done
done
