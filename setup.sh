#!/bin/bash

mkdir -p ~/cutils/bin
mkdir -p ~/cutils/include
mkdir -p obj

echo "CPATH=$CPATH:~/cutils/inlcude" >> ~/.bashrc
echo "LIBRARY_PATH=$LIBRARY_PATH:~/cutils/bin" >> ~/.bashrc
echo "LD_LIBRARY_PATH=$LD_LIBRARY_PATH:~/cutils/bin" >> ~/.bashrc

source ~/.bashrc

make
