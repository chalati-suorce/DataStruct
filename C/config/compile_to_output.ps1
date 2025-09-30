# Compile C files and output exe to output directory
param(
    [Parameter(Mandatory=$true)]
    [string]$SourceFile
)

# Get source filename (without extension)
$outputDir = "output"
$exeName = [System.IO.Path]::GetFileNameWithoutExtension($SourceFile) + ".exe"
$outputPath = Join-Path $outputDir $exeName

# Check if output directory exists, create if not
if (!(Test-Path $outputDir)) {
    New-Item -ItemType Directory -Path $outputDir -Force | Out-Null
}

# Check if source file exists
if (!(Test-Path $SourceFile)) {
    Write-Error "Source file '$SourceFile' not found"
    exit 1
}

# Compile file
Write-Host "Compiling $SourceFile to $outputPath..." -ForegroundColor Green

$extension = [System.IO.Path]::GetExtension($SourceFile).ToLower()
switch ($extension) {
    ".c" {
        gcc $SourceFile -o $outputPath
    }
    default {
        Write-Error "Unsupported file type: $extension"
        exit 1
    }
}

# Check if compilation was successful
if ($LASTEXITCODE -eq 0) {
    Write-Host "Successfully compiled to $outputPath" -ForegroundColor Green
} else {
    Write-Error "Compilation failed"
    exit 1
}
