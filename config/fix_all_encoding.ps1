# PowerShell脚本：修复所有编码问题
Write-Host "正在修复所有编码问题..." -ForegroundColor Green

# 设置终端编码为UTF-8
Write-Host "设置终端编码为UTF-8..." -ForegroundColor Cyan
chcp 65001 | Out-Null
[Console]::OutputEncoding = [System.Text.Encoding]::UTF8
$OutputEncoding = [System.Text.Encoding]::UTF8

# 转换所有C/C++文件编码为UTF-8
Write-Host "转换所有C/C++文件编码为UTF-8..." -ForegroundColor Cyan
$files = Get-ChildItem -Recurse -Include "*.c", "*.cpp", "*.h", "*.hpp"

if ($files.Count -eq 0) {
    Write-Host "未找到C/C++源文件。" -ForegroundColor Yellow
} else {
    Write-Host "找到 $($files.Count) 个C/C++源文件：" -ForegroundColor Cyan
    foreach ($file in $files) {
        try {
            $content = Get-Content -Path $file.FullName -Raw
            $content | Out-File -FilePath $file.FullName -Encoding UTF8
            Write-Host "✓ 已转换: $($file.Name)" -ForegroundColor Green
        }
        catch {
            Write-Host "✗ 转换失败: $($file.Name)" -ForegroundColor Red
        }
    }
}

# 验证设置
Write-Host "`n编码设置完成！" -ForegroundColor Green
Write-Host "当前终端编码：" -ForegroundColor Cyan
chcp
Write-Host "`n测试中文显示：" -ForegroundColor Cyan
Write-Host "中文测试" -ForegroundColor Yellow

Write-Host "`n按任意键继续..." -ForegroundColor Gray
Read-Host
