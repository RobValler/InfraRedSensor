#!/bin/bash
set -e
cd build

. /opt/ros/humble/setup.bash
#. install/setup.bash

conan install .. 

# conanfile.txt
cmake ..
make -j16

