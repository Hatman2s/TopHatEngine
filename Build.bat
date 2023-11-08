@echo off
call Externs\Premake\premake-5.0.0-beta2-windows\premake5.exe vs2022
IF %ERRORLEVELS% NEQ 0 (PAUSE)