@echo off
pushd %~dp0\..\
call Newt\vendor\premake\bin\premake5.exe vs2022
popd
PAUSE