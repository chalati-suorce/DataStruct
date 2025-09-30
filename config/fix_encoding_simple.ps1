# Simple encoding fix script
Write-Host "Fixing encoding issues..." -ForegroundColor Green

# Set console encoding to UTF-8
chcp 65001 | Out-Null
[Console]::OutputEncoding = [System.Text.Encoding]::UTF8
$OutputEncoding = [System.Text.Encoding]::UTF8

# Convert all C/C++ files to UTF-8
$files = Get-ChildItem -Recurse -Include "*.c", "*.cpp", "*.h", "*.hpp"

if ($files.Count -eq 0) {
    Write-Host "No C/C++ files found." -ForegroundColor Yellow
} else {
    Write-Host "Found $($files.Count) C/C++ files" -ForegroundColor Cyan
    foreach ($file in $files) {
        try {
            $content = Get-Content -Path $file.FullName -Raw
            $content | Out-File -FilePath $file.FullName -Encoding UTF8
            Write-Host "Converted: $($file.Name)" -ForegroundColor Green
        }
        catch {
            Write-Host "Failed: $($file.Name)" -ForegroundColor Red
        }
    }
}

Write-Host "Encoding fix completed!" -ForegroundColor Green
Write-Host "Current code page:" -ForegroundColor Cyan
chcp
Write-Host "Chinese test: 中文测试" -ForegroundColor Yellow
