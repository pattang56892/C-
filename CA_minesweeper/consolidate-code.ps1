# consolidate-code.ps1 - Enhanced version with unique naming and Docs folder
param(
    [string]$CustomName = $null,
    [switch]$ListFiles = $false
)

# Create Docs directory if it doesn't exist
if (!(Test-Path "Docs")) {
    New-Item -ItemType Directory -Path "Docs" -Force | Out-Null
    Write-Host "Created Docs/ directory"
}

# Generate unique filename with timestamp
$timestamp = Get-Date -Format "yyyyMMdd_HHmmss"
$gitHash = ""

# Try to get git commit hash for more unique naming
try {
    $gitHash = (git rev-parse --short HEAD 2>$null)
    if ($gitHash) {
        $gitHash = "_$gitHash"
    }
} catch {
    # Git not available or not a git repo, continue without hash
}

# Determine output filename
if ($CustomName) {
    $OutputFile = "Docs/minesweeper-consolidated_${CustomName}_${timestamp}${gitHash}.txt"
} else {
    $OutputFile = "Docs/minesweeper-consolidated_${timestamp}${gitHash}.txt"
}

$files = @(
    "minesweeper_core.h",
    "minesweeper_core.cpp", 
    "minesweeper_terminal.cpp",
    "main.cpp",
    "Web_Interface/minesweeper.html",
    "projectTree.txt"
)

# Optional files that might not exist yet
$optionalFiles = @(
    "minesweeper_qt.cpp",
    "minesweeper_sdl.cpp",
    "minesweeper_imgui.cpp",
    ".gitignore"
)

# If -ListFiles switch is used, just show what would be consolidated
if ($ListFiles) {
    Write-Host "Files that would be consolidated:" -ForegroundColor Green
    foreach ($file in ($files + $optionalFiles)) {
        if (Test-Path $file) {
            Write-Host "  ✓ $file" -ForegroundColor Green
        } else {
            Write-Host "  ✗ $file (not found)" -ForegroundColor Yellow
        }
    }
    Write-Host "`nOutput would be saved to: $OutputFile" -ForegroundColor Cyan
    return
}

$output = @"
=== MINESWEEPER PROJECT CONSOLIDATED ===
Generated: $(Get-Date -Format "yyyy-MM-dd HH:mm:ss")
Git Hash: $(if ($gitHash) { $gitHash.Substring(1) } else { "Not available" })
Files included: $($files -join ', ')
Total interfaces: Terminal (C++), Web (HTML/CSS/JS)
Project Status: 2 of 5 interfaces complete

"@

$filesProcessed = 0
$totalLines = 0

# Process main files
foreach ($file in $files) {
    if (Test-Path $file) {
        $content = Get-Content $file -Raw
        $lineCount = ($content -split "`n").Count
        $totalLines += $lineCount
        
        $output += "`n" + "="*70 + "`n"
        $output += "FILE: $file (Lines: $lineCount)`n"
        $output += "="*70 + "`n"
        
        # Add file type info for context
        if ($file.EndsWith(".h")) {
            $output += "// C++ Header File - Game Logic Interface`n"
        } elseif ($file.EndsWith(".cpp")) {
            $output += "// C++ Source File - Implementation`n"
        } elseif ($file.EndsWith(".html")) {
            $output += "<!-- HTML/CSS/JavaScript - Web Interface -->`n"
        } elseif ($file.EndsWith(".txt")) {
            $output += "# Text Documentation`n"
        }
        
        $output += $content
        $output += "`n"
        $filesProcessed++
        Write-Host "✓ Processed: $file ($lineCount lines)" -ForegroundColor Green
    } else {
        $output += "`nWARNING: $file not found`n"
        $output += "Expected location: $(Resolve-Path . -Relative)/$file`n"
        Write-Host "✗ Missing: $file" -ForegroundColor Yellow
    }
}

# Process optional files
foreach ($file in $optionalFiles) {
    if (Test-Path $file) {
        $content = Get-Content $file -Raw
        $lineCount = ($content -split "`n").Count
        $totalLines += $lineCount
        
        $output += "`n" + "="*70 + "`n"
        $output += "FILE: $file (Lines: $lineCount) [OPTIONAL]`n"
        $output += "="*70 + "`n"
        
        $output += $content
        $output += "`n"
        $filesProcessed++
        Write-Host "✓ Added optional: $file ($lineCount lines)" -ForegroundColor Cyan
    }
}

# Add comprehensive summary
$output += "`n" + "="*70 + "`n"
$output += "CONSOLIDATION SUMMARY`n"
$output += "="*70 + "`n"
$output += "Generation timestamp: $(Get-Date -Format "yyyy-MM-dd HH:mm:ss")`n"
$output += "Git commit hash: $(if ($gitHash) { $gitHash.Substring(1) } else { "Not available" })`n"
$output += "Total lines consolidated: $totalLines`n"
$output += "Files successfully processed: $filesProcessed`n"
$output += "Output file: $OutputFile`n"
$output += "File size: $([math]::Round(($output.Length / 1KB), 2)) KB`n"
$output += "`nInterfaces Status:`n"
$output += "  [X] Core Game Logic     - Complete`n"
$output += "  [X] Terminal Interface  - Complete`n"
$output += "  [X] Web Interface       - Complete`n"
$output += "  [ ] Qt GUI Interface    - Planned`n"
$output += "  [ ] SDL2 Interface      - Planned`n"
$output += "  [ ] ImGui Interface     - Planned`n"
$output += "`nNext steps: Choose next interface to implement`n"
$output += "Project folder structure includes Docs/ (git ignored)`n"

# Save to Docs folder
$output | Out-File -FilePath $OutputFile -Encoding UTF8

# Final output
Write-Host "`n" + "="*50 -ForegroundColor Magenta
Write-Host "CONSOLIDATION COMPLETE" -ForegroundColor Magenta
Write-Host "="*50 -ForegroundColor Magenta
Write-Host "Output file: $OutputFile" -ForegroundColor Green
Write-Host "Total lines: $totalLines" -ForegroundColor Cyan
Write-Host "Files processed: $filesProcessed" -ForegroundColor Cyan
Write-Host "File size: $([math]::Round((Get-Item $OutputFile).Length / 1KB, 2)) KB" -ForegroundColor Cyan

# List recent consolidations
$recentFiles = Get-ChildItem "Docs/minesweeper-consolidated_*.txt" | Sort-Object LastWriteTime -Descending | Select-Object -First 5
if ($recentFiles.Count -gt 1) {
    Write-Host "`nRecent consolidations in Docs/:" -ForegroundColor Yellow
    foreach ($file in $recentFiles) {
        $age = [math]::Round((New-TimeSpan $file.LastWriteTime (Get-Date)).TotalHours, 1)
        Write-Host "  $($file.Name) (${age}h ago)" -ForegroundColor Gray
    }
}

Write-Host "`nNote: Docs/ folder is git ignored - safe for documentation" -ForegroundColor Green