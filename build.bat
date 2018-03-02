set project_dir=%~dp0
set configuration=MinSizeRel
call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvars64.bat"
cd %project_dir%
msbuild build\xrig.sln /p:Configuration=%configuration%
xcopy libuv-1.14.1-x64\libuv.dll build\%configuration%\ /Y
xcopy devcon\devcon.exe build\%configuration%\ /Y
(
echo @echo off
echo cd %%~dp0
echo set yyyy=%%date:~10,4%%
echo set mm=%%date:~4,2%%
echo set dd=%%date:~7,2%%
echo set hh=%%time:~0,2%%
echo if "%%hh:~0,1%%" == " " set hh=0%%hh:~1,1%%
echo set mm=%%time:~3,2%%
echo set ss=%%time:~6,2%%
echo xrig.exe --colors --log=xrig_%%yyyy%%%%mm%%%%dd%%_%%hh%%%%mm%%%%ss%%.log
echo pause
) > build\%configuration%\run.bat
(
echo @echo off
echo cd %%~dp0
echo devcon.exe disable "PCI\VEN_1002&DEV_687F"
echo timeout /t 5
echo devcon.exe enable "PCI\VEN_1002&DEV_687F"
echo timeout /t 5
echo set yyyy=%%date:~10,4%%
echo set mm=%%date:~4,2%%
echo set dd=%%date:~7,2%%
echo set hh=%%time:~0,2%%
echo if "%%hh:~0,1%%" == " " set hh=0%%hh:~1,1%%
echo set mm=%%time:~3,2%%
echo set ss=%%time:~6,2%%
echo xrig.exe --colors --log=xrig_%%yyyy%%%%mm%%%%dd%%_%%hh%%%%mm%%%%ss%%.log
echo pause
) > build\%configuration%\run_with_reset.bat
