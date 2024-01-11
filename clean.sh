#!/bin/bash

clear

path=$(
    cd "$(dirname "$0")"
    pwd -P
)

echo "path:" $path

cd $path/../build/debug

"/usr/bin/make" clean -j8