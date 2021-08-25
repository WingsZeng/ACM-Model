@echo off
:loop
    X-data.exe > X.in
    X.exe < X.in > X.out
    X-bf.exe < X.in > X-bf.out
    fc X.out X-bf.out
    if not errorlevel 1 goto loop
    pause
goto loop
