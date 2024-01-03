#!/bin/bash

clear

cd /home/gino/Projects/Qt/gKarate/build/Debug

"/home/gino/Tools/Qt/6.5.3/gcc_64/bin/qmake" /home/gino/Projects/Qt/gKarate/gKarate/gKarate.pro -spec linux-g++ CONFIG+=debug CONFIG+=qml_debug

"/usr/bin/make" -f /home/gino/Projects/Qt/gKarate/build/Debug/Makefile qmake_all

"/usr/bin/make" -j8