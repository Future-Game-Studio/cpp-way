@echo off
rem set some flags for warnings output and compiler optimization
set flags=-W -Wall -O3 -std=c++2a -Wno-unknown-pragmas -Wno-clobbered
set compiler=g++
rem call g++ or mingw8 compiler
if not exist "../app" mkdir "../app"
%compiler% %flags% -g "../src/%1/%1.cpp" -o "../app/app-%1.exe"