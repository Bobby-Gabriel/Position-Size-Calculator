# PowerShell script to create desktop shortcut
$WScriptShell = New-Object -ComObject WScript.Shell
$Desktop = [System.Environment]::GetFolderPath('Desktop')
$ShortcutPath = Join-Path $Desktop "Position Size Calculator.lnk"
$Shortcut = $WScriptShell.CreateShortcut($ShortcutPath)
$Shortcut.TargetPath = Join-Path $PSScriptRoot "bin\PositionSizeCalculator.exe"
$Shortcut.WorkingDirectory = Join-Path $PSScriptRoot "bin"
$Shortcut.Description = "Position Size Calculator"
$Shortcut.Save()

Write-Host "Desktop shortcut created at: $ShortcutPath"
