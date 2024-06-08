@echo off

set CFLAGS=-Wextra -Wall -std=c11 -pedantic -O2 -mwindows
set SRC=%~dp0src\
set OUT=%~dp0out\

del /Q out
mkdir out 2> NUL
windres %SRC%icon.rc -o %OUT%icon.o
gcc -o %OUT%tlf.exe %SRC%main.c %OUT%icon.o %CFLAGS% 
