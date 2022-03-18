@echo off

for /f "tokens=2 delims==" %%a in ('wmic OS Get localdatetime /value') do set "dt=%%a"
set "date=%dt:~0,4%_%dt:~4,2%_%dt:~6,2%"

ROBOCOPY "data" "target\debug\%date%\data" /mir /nfl /ndl /njh /njs /np /ns /nc > nul
ROBOCOPY "src" "target\debug\%date%\source\src" /mir /nfl /ndl /njh /njs /np /ns /nc > nul
ROBOCOPY "include" "target\debug\%date%\source\include" /mir /nfl /ndl /njh /njs /np /ns /nc >nul

rem set "start=%dt:~12,4%"

gcc src\main.c -o target\debug\%date%\Anbray.exe -lraylib -lgdi32 -lwinmm -g

rem set "end=%dt:~12,4%-%start%"
rem echo %end%