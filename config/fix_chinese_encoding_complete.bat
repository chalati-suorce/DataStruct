@echo off
chcp 65001 >nul
echo ========================================
echo    中文编码问题完整解决方案
echo ========================================
echo.

echo [1/4] 设置终端编码为UTF-8...
chcp 65001 >nul
echo ✓ 终端编码已设置为UTF-8 (65001)

echo.
echo [2/4] 设置PowerShell编码...
powershell -Command "[Console]::OutputEncoding = [System.Text.Encoding]::UTF8; $OutputEncoding = [System.Text.Encoding]::UTF8"
echo ✓ PowerShell编码已设置为UTF-8

echo.
echo [3/4] 转换所有C/C++文件编码...
powershell -Command "Get-ChildItem -Recurse -Include '*.c','*.cpp','*.h','*.hpp' | ForEach-Object { 
    try { 
        Get-Content $_.FullName -Raw | Out-File -FilePath $_.FullName -Encoding UTF8 -Force
        Write-Host '✓ 已转换:' $_.Name -ForegroundColor Green
    } catch { 
        Write-Host '✗ 转换失败:' $_.Name -ForegroundColor Red
    }
}"

echo.
echo [4/4] 测试中文显示...
echo ========================================
echo 中文测试 - 如果显示正常，说明编码问题已解决
echo 如果仍然乱码，请检查终端字体设置
echo ========================================
echo.

echo 解决方案建议：
echo 1. 在VSCode中：设置 -> 搜索"terminal font" -> 设置字体为支持中文的字体
echo 2. 在Windows终端中：设置 -> 默认值 -> 外观 -> 字体 -> 选择支持中文的字体
echo 3. 推荐字体：Microsoft YaHei Mono, SimSun-ExtB, NSimSun, 等宽字体
echo.

echo 按任意键查看当前字体设置...
pause >nul

echo.
echo 当前终端信息：
echo 编码页: 65001 (UTF-8)
echo 测试中文: 中文测试
echo.
echo 如果中文显示正常，问题已解决！
echo 如果仍然乱码，请按照上面的建议更改终端字体
pause
