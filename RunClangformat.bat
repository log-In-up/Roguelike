@echo off
::Batch file to run clangformat on project
::Requries installed C++ Clang tools in Visual studio community 2022 to work

::Step 1 : set projects folders and file types
set PROJECT_FOLDERS=Roguelike Engine EngineTest
set FILE_TYPES="*.cpp" "*.h"
set CLANG_FORMAT_CONFIG=%~dp0.clang-format


::Step 2 : set clang-format path and check if it exists
set CLANG_FORMAT_PATH="C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\Llvm\bin\clang-format.exe"
IF not exist %CLANG_FORMAT_PATH% (
	echo clang-format not found at %CLANG_FORMAT_PATH%
::Zero return code to prevent building failing
	exit /b 0
)

::Step 3 : run clang-format
for %%a in (%PROJECT_FOLDERS%) do (
	cd ./%%a
	for /r %%b in (%FILE_TYPES%) do (
		%CLANG_FORMAT_PATH% -i --style=file:%CLANG_FORMAT_CONFIG% %%b)
	cd ../
)
