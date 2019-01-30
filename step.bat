@echo off
set p1=2.exe
set p2=2_brute.exe
set p3=gen.exe
set /A ti = 1
:LOP1
    echo LOOP:%ti%
    echo 27 > exchange.txt
    %p3% < exchange.txt
    %p1% < bat.in > out1.txt
    %p2% < bat.in > out2.txt
    fc out1.txt out2.txt
    set /A ti = %ti% + 1
if ERRORLEVEL 1 exit
if %ti% LEQ 10000 goto LOP1