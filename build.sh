#!/bin/bash

clear

path=$(
cd "$(dirname "$0")"
    pwd -P
)

echo "path:" $path

cd $path/../build/debug

bear -- cmake --build ./ --target all -j8

cp compile_commands.json ../../gKarate