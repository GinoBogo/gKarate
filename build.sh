#!/bin/bash

clear

path=$(
cd "$(dirname "$0")"
    pwd -P
)

echo "path:" $path

cd $path/../build/debug

"/home/gino/Tools/Qt/6.5.3/gcc_64/bin/qmake" $path/../gKarate/gKarate.pro -spec linux-g++ CONFIG+=debug CONFIG+=qml_debug

"/usr/bin/make" -f Makefile qmake_all

"/usr/bin/make" -j8