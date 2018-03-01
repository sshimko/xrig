cd %~dp0
timeout /t 10
devcon.exe disable "PCI\VEN_1002&DEV_687F"
timeout /t 5
devcon.exe enable "PCI\VEN_1002&DEV_687F"
timeout /t 5
OverdriveNTool.exe -p1default -p2default -p3default -p4default -p5default -p6default
timeout /t 5

@echo off
set yyyy=%date:~10,4%
set mm=%date:~4,2%
set dd=%date:~7,2%
set hh=%time:~0,2%
if "%hh:~0,1%" == " " set hh=0%hh:~1,1%
set mm=%time:~3,2%
set ss=%time:~6,2%

C:\Users\robert\Downloads\xrig\build\MinSizeRel\xrig.exe --log-file=xrig_%yyyy%%mm%%dd%_%hh%%mm%%ss%.log
pause
