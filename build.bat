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
echo xrig.exe
echo pause
) > build\%configuration%\run.bat
(
echo @echo off
echo cd %%~dp0
echo devcon.exe disable "PCI\VEN_1002&DEV_687F"
echo timeout /t 5
echo devcon.exe enable "PCI\VEN_1002&DEV_687F"
echo timeout /t 5
echo xrig.exe
echo pause
) > build\%configuration%\run_with_reset.bat
