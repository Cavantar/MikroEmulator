@echo off

if not exist ..\build mkdir ..\build
pushd ..\build

set CompilerOptions=/FC /Zi /EHsc /MD /MP /wd4503 /wd4312 /nologo /FeMikroEmulator.exe

cl /Od %CompilerOptions% ..\src\main.cpp ..\src\MikroEmulator.cpp user32.lib

popd
