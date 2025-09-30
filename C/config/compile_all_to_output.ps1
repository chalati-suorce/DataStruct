# PowerShell script: Batch compile all C files to output directories
Write-Host "Batch compiling all C files to output directories..." -ForegroundColor Green

# Find all C files
$cFiles = Get-ChildItem -Path "..\" -Recurse -Include "*.c"

if ($cFiles.Count -eq 0) {
    Write-Host "No C files found." -ForegroundColor Yellow
    exit
}

Write-Host "Found $($cFiles.Count) C files:" -ForegroundColor Cyan

foreach ($file in $cFiles) {
    try {
        # Compile file
        .\compile_to_output.ps1 -SourceFile $file.FullName
    }
    catch {
        Write-Host "Compilation failed: $($file.Name) - $($_.Exception.Message)" -ForegroundColor Red
    }
}

Write-Host "Batch compilation completed!" -ForegroundColor Green
Write-Host "Press any key to continue..." -ForegroundColor Gray
Read-Host
