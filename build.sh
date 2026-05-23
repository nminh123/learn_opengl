#!/bin/bash

#if first time u use application, create build folder
if [ ! -d "./build" ]; then
    mkdir build/
fi

cd build/ || exit

#build application
cmake ..
cmake --build .

#run application
./bin/app

cd ..