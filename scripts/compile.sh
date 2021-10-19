#!/bin/bash 
g++  -std=c++2a -Wno-unknown-pragmas -Wall -I. -o "../src/$1/$1.o" -c "../src/$1/$1.cpp"
[ ! -d "../app" ] && mkdir "../app"
g++ "../src/$1/$1.o" -o "../app/app-$1"