# PowerShell script: Convert C/C++ source files to UTF-8 encoding
Write-Host "Checking and converting file encoding to UTF-8..." -ForegroundColor Green

# Set console encoding to UTF-8
[Console]::OutputEncoding = [System.Text.Encoding]::UTF8
$OutputEncoding = [System.Text.Encoding]::UTF8

# Find all C/C++ source files
$files = Get-ChildItem -Recurse -Include "*.c", "*.cpp", "*.h", "*.hpp"

if ($files.Count -eq 0) {
    Write-Host "No C/C++ source files found." -ForegroundColor Yellow
    exit
}

Write-Host "Found $($files.Count) C/C++ source files:" -ForegroundColor Cyan

foreach ($file in $files) {
    try {
        # Read file content
        $content = Get-Content -Path $file.FullName -Raw
        
        # Convert to UTF-8
        $content | Out-File -FilePath $file.FullName -Encoding UTF8
        
        Write-Host "Converted: $($file.Name)" -ForegroundColor Green
    }
    catch {
        Write-Host "Failed to convert: $($file.Name) - $($_.Exception.Message)" -ForegroundColor Red
    }
}

Write-Host "File encoding conversion completed!" -ForegroundColor Green
Write-Host "Press any key to continue..." -ForegroundColor Gray
Read-Host
