#!/bin/bash

output=""

for arg in $*; do
    output="$arg\n$output"
done

printf $output
