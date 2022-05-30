@echo off
pushd %~dp0\..\
call Newt\vendor\premake\bin\premake5.exe vs2019
popd
PAUSE