@echo off
@REM C:\jules-dev\tools\compilers\mingw64\bin\
cd "C:\Users\jules\OneDrive\Bureau\css_parser\src"
gcc -static-libgcc -static-libstdc++ -std=gnu11 "main.c" -o "../build/css.exe"
cd "C:\Users\jules\OneDrive\Bureau\css_parser"
"./build/css.exe" "C:\Users\jules\OneDrive\Bureau\css_parser\test\test.scss"