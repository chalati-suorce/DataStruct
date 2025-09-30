# PowerShell脚本：将C/C++源文件转换为UTF-8编码
Write-Host "正在检查并转换文件编码为UTF-8..." -ForegroundColor Green

# 设置控制台编码为UTF-8
[Console]::OutputEncoding = [System.Text.Encoding]::UTF8
$OutputEncoding = [System.Text.Encoding]::UTF8

# 查找所有C/C++源文件
$files = Get-ChildItem -Recurse -Include "*.c", "*.cpp", "*.h", "*.hpp"

if ($files.Count -eq 0) {
    Write-Host "未找到C/C++源文件。" -ForegroundColor Yellow
    exit
}

Write-Host "找到 $($files.Count) 个C/C++源文件：" -ForegroundColor Cyan

foreach ($file in $files) {
    try {
        # 读取文件内容
        $content = Get-Content -Path $file.FullName -Raw
        
        # 检测当前编码
        $encoding = [System.Text.Encoding]::GetEncoding("GB2312")
        $bytes = $encoding.GetBytes($content)
        
        # 转换为UTF-8
        $utf8Content = [System.Text.Encoding]::UTF8.GetString($bytes)
        
        # 写回文件
        $utf8Content | Out-File -FilePath $file.FullName -Encoding UTF8
        
        Write-Host "✓ 已转换: $($file.Name)" -ForegroundColor Green
    }
    catch {
        Write-Host "✗ 转换失败: $($file.Name) - $($_.Exception.Message)" -ForegroundColor Red
    }
}

Write-Host "`n文件编码转换完成！" -ForegroundColor Green
Write-Host "现在终端应该能正确显示中文了。" -ForegroundColor Cyan
Write-Host "按任意键继续..." -ForegroundColor Gray
$null = $Host.UI.RawUI.ReadKey("NoEcho,IncludeKeyDown")
