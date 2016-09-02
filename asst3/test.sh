#!/bin/bash

if [[ $# -ne 1 ]]
then
    echo "Usage: test.sh CODE_DIR"
    exit
fi

# Copy EuclideanVector code into this dir.
CODE_DIR="$1"
cp "${CODE_DIR}Graph.temp" .
cp "${CODE_DIR}Graph.h" .

# Compile our test-suite..
make

# Run the tests.
./GraphTester
