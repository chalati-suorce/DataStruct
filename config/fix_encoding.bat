@echo off
chcp 65001 >nul
echo 已设置终端编码为UTF-8
echo.
echo 检查项目中的文件编码...
powershell -Command "Get-ChildItem -Recurse -Include *.c,*.cpp,*.h,*.hpp | ForEach-Object { Write-Host ('文件: {0}' -f $_.Name) }"
echo.
echo 如果需要转换文件编码，请使用以下命令：
echo powershell -Command "Get-Content '文件名' | Out-File -Encoding UTF8 '文件名'"
echo.
pause
