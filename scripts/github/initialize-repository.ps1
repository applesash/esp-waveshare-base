param([Parameter(Mandatory=$true)][string]$Owner,[Parameter(Mandatory=$true)][string]$Repository)
$ErrorActionPreference='Stop'
gh auth status
if(-not (Test-Path .git)){ git init }
git branch -M main
git remote remove origin 2>$null
git remote add origin "https://github.com/$Owner/$Repository.git"
Write-Host 'Remote configured over HTTPS. Repository creation/visibility must follow applicable organizational policy.'
