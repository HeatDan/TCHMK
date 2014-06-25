@ECHO off
set /P aFileName="Enter A file name: "

set /P operation="Enter operation [+ - * / %%]: "

set /P bFileName="Enter B file name: "

set /P resFileName="Enter result file name: "

set /P b="-b: "

@ECHO on
python TCHMK_2.py "%aFileName%" "%operation%" "%bFileName%" "%resFileName%" "%b%"
pause