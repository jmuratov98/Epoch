@echo off
pushd %~dp0\..\
call lib\bin\premake5\premake5.exe vs2019
popd
PAUSE