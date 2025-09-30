# Final solution for Chinese encoding issues
Write-Host "========================================" -ForegroundColor Cyan
Write-Host "    Chinese Encoding Complete Solution" -ForegroundColor Cyan
Write-Host "========================================" -ForegroundColor Cyan
Write-Host ""

# Step 1: Set console encoding to UTF-8
Write-Host "[1/4] Setting console encoding to UTF-8..." -ForegroundColor Yellow
chcp 65001 | Out-Null
[Console]::OutputEncoding = [System.Text.Encoding]::UTF8
$OutputEncoding = [System.Text.Encoding]::UTF8
Write-Host "✓ Console encoding set to UTF-8 (65001)" -ForegroundColor Green

Write-Host ""

# Step 2: Convert all C/C++ files to UTF-8
Write-Host "[2/4] Converting all C/C++ files to UTF-8..." -ForegroundColor Yellow
$files = Get-ChildItem -Recurse -Include "*.c", "*.cpp", "*.h", "*.hpp"

if ($files.Count -eq 0) {
    Write-Host "No C/C++ files found." -ForegroundColor Yellow
} else {
    Write-Host "Found $($files.Count) C/C++ files:" -ForegroundColor Cyan
    foreach ($file in $files) {
        try {
            $content = Get-Content -Path $file.FullName -Raw
            $content | Out-File -FilePath $file.FullName -Encoding UTF8 -Force
            Write-Host "✓ Converted: $($file.Name)" -ForegroundColor Green
        }
        catch {
            Write-Host "✗ Failed: $($file.Name)" -ForegroundColor Red
        }
    }
}

Write-Host ""

# Step 3: Test Chinese display
Write-Host "[3/4] Testing Chinese display..." -ForegroundColor Yellow
Write-Host "========================================" -ForegroundColor Cyan
Write-Host "Chinese Test - If displayed correctly, encoding is fixed" -ForegroundColor White
Write-Host "If still garbled, check terminal font settings" -ForegroundColor White
Write-Host "========================================" -ForegroundColor Cyan

Write-Host ""

# Step 4: Provide solution suggestions
Write-Host "[4/4] Solution Suggestions:" -ForegroundColor Yellow
Write-Host "1. In VSCode: Settings -> Search 'terminal font' -> Set font to Chinese-supported font" -ForegroundColor White
Write-Host "2. In Windows Terminal: Settings -> Defaults -> Appearance -> Font -> Choose Chinese-supported font" -ForegroundColor White
Write-Host "3. Recommended fonts: Microsoft YaHei Mono, SimSun-ExtB, NSimSun, monospace fonts" -ForegroundColor White

Write-Host ""

# Show current terminal info
Write-Host "Current Terminal Information:" -ForegroundColor Cyan
Write-Host "Code Page: 65001 (UTF-8)" -ForegroundColor White
Write-Host "Chinese Test: 中文测试" -ForegroundColor Yellow

Write-Host ""

if ($Host.Name -eq "ConsoleHost") {
    Write-Host "If Chinese displays correctly, problem is solved!" -ForegroundColor Green
    Write-Host "If still garbled, please change terminal font as suggested above" -ForegroundColor Red
    Write-Host ""
    Write-Host "Press any key to continue..." -ForegroundColor Gray
    $null = $Host.UI.RawUI.ReadKey("NoEcho,IncludeKeyDown")
} else {
    Write-Host "Script completed. Check Chinese display above." -ForegroundColor Green
}
