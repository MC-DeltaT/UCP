#!/bin/bash

grep -E '(^|[[:space:]])([0-9]{1,3}?\.){3}[0-9]{1,3}([[:space:]]|$)' logfile

