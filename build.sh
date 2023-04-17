#!/bin/bash
mkdir -p build/linux
cd build/linux
cmake -DCONFIG_TYCOMMANDER_BUILD=0 -DCONFIG_TYUPLOADER_BUILD=0 ../..
make
