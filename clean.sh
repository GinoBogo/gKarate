#!/bin/bash

clear

path=$(
    cd "$(dirname "$0")"
    pwd -P
)

echo "path:" $path

cd $path/../build/debug

cmake --build ./ --target clean -j8