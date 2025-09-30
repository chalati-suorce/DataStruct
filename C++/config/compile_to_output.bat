@echo off
chcp 65001 >nul
REM Compile C/C++ files and output exe to output directory
setlocal

REM Check parameters
if "%~1"=="" (
    echo Usage: %~nx0 source_file.c
    echo Example: %~nx0 example.c
    exit /b 1
)

REM Get source filename (without extension)
set "source_file=%~1"
set "output_dir=output"
set "exe_name=%~n1.exe"

REM Check if output directory exists, create if not
if not exist "%output_dir%" mkdir "%output_dir%"

REM Compile file
echo Compiling %source_file% to %output_dir%\%exe_name%...
if "%~x1"==".c" (
    gcc "%source_file%" -o "%output_dir%\%exe_name%"
) else if "%~x1"==".cpp" (
    g++ "%source_file%" -o "%output_dir%\%exe_name%"
) else (
    echo Unsupported file type: %~x1
    exit /b 1
)

REM Check if compilation was successful
if %errorlevel% equ 0 (
    echo Successfully compiled to %output_dir%\%exe_name%
) else (
    echo Compilation failed
    exit /b 1
)
