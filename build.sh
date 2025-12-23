#!/bin/bash

if [ ! -d "build" ]; then
  mkdir build
fi

cd build

# 3. Run CMake
cmake ..

make -j$(nproc) 
