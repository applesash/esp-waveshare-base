param([string]$Remote='origin',[string]$Tag='')
$ErrorActionPreference='Stop'
if(-not (Test-Path .git)){ throw 'Not a Git repository.' }
git fetch $Remote --tags
if(-not $Tag){ $Tag=(git tag --sort=-creatordate | Where-Object { $_ -match '^phase-[0-9]{2}-complete$' } | Select-Object -First 1) }
if(-not $Tag){ throw 'No completed phase tag found.' }
$localCommit=(git rev-list -n 1 $Tag).Trim()
$remoteLine=(git ls-remote --tags $Remote "refs/tags/$Tag^{}").Trim()
if(-not $remoteLine){ $remoteLine=(git ls-remote --tags $Remote "refs/tags/$Tag").Trim() }
if(-not $remoteLine){ throw "Remote tag $Tag not found." }
$remoteCommit=($remoteLine -split '\s+')[0]
if($remoteCommit -ne $localCommit){ throw "Tag mismatch: local $localCommit remote $remoteCommit" }
$snapshot="artifacts/phase-snapshots/$Tag.zip"
if(-not (Test-Path $snapshot)){ throw "Snapshot missing: $snapshot" }
$sha=(Get-FileHash $snapshot -Algorithm SHA256).Hash
Write-Host 'RECOVERY CHECK PASS'
Write-Host "Tag: $Tag"
Write-Host "Commit: $localCommit"
Write-Host "Snapshot: $snapshot"
Write-Host "SHA256: $sha"
