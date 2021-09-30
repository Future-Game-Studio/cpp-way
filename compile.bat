@echo off
rem set some flags for warnings output and compiler optimization
set flags=-W -Wall -O3
set compiler=g++
rem call g++ or mingw8 compiler
if not exist app mkdir app
%compiler% %flags% -g %1.cpp -o "app/app-%1.exe"