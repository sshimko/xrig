set build_dir=%~dp0
call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvars64.bat"
cd %build_dir%
msbuild build\xrig.sln /p:Configuration=MinSizeRel
