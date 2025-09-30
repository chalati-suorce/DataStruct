@echo off
chcp 65001 >nul
echo 批量编译所有C文件到output目录...
echo.

REM 查找所有C文件并编译
for /r "C:\" %%f in (*.c) do (
    echo 编译: %%~nxf
    call compile_to_output.bat "%%f"
    echo.
)

echo 批量编译完成！
pause
