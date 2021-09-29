#!/bin/bash 
g++ -std=c++2a -Wall -I. -o $1.o -c $1.cpp
[ ! -d app ] && mkdir app
g++ $1.o -o app/app-$1