param(
  [Parameter(Mandatory=$true)][ValidatePattern('^PHASE-[0-9]{2}$')][string]$Phase,
  [Parameter(Mandatory=$true)][string]$PhaseName,
  [string]$Remote='origin'
)
$ErrorActionPreference='Stop'
$tag=$Phase.ToLower() + '-complete'
$phaseFile=Get-ChildItem 'docs/phases' -Filter ($Phase.Replace('-','_') + '_*.md') | Select-Object -First 1
if(-not $phaseFile){ throw "No phase document found for $Phase" }
if(-not (Test-Path .git)){ throw 'Not a Git repository.' }
if(git status --porcelain | Select-String '^UU|^AA|^DD'){ throw 'Unresolved Git conflicts exist.' }
gh auth status | Out-Host
if($LASTEXITCODE -ne 0){ throw 'GitHub authentication unavailable.' }
git remote get-url $Remote | Out-Host
if($LASTEXITCODE -ne 0){ throw "Remote $Remote is unavailable." }
if(git tag --list $tag){ throw "Local tag $tag already exists and is immutable." }
$remoteTag = git ls-remote --tags $Remote "refs/tags/$tag"
if($remoteTag){ throw "Remote tag $tag already exists and is immutable." }
Write-Host 'Before continuing, required tests, evidence, traceability, PROJECT_STATUS, and RESTORE_POINTS must already be updated.'
$answer=Read-Host 'Type GATE-PASSED to create and publish the checkpoint'
if($answer -ne 'GATE-PASSED'){ throw 'Checkpoint cancelled.' }
git add --all
$forbidden = git diff --cached --name-only | Select-String '(^|/)(\.env|.*\.pem|.*\.key|sdkconfig|build/|node_modules/)'
if($forbidden){ throw "Potential secret/generated files staged:`n$forbidden" }
git commit -m "[$Phase] $PhaseName - Gate Passed"
if($LASTEXITCODE -ne 0){ throw 'Commit failed.' }
$commit=(git rev-parse HEAD).Trim()
git tag -a $tag -m "$Phase $PhaseName - Gate Passed" $commit
if($LASTEXITCODE -ne 0){ throw 'Annotated tag creation failed.' }
$branch=(git branch --show-current).Trim()
if(-not $branch){ throw 'Detached HEAD is not allowed for checkpoint publishing.' }
git push -u $Remote $branch
if($LASTEXITCODE -ne 0){ throw 'Branch push failed.' }
git push $Remote "refs/tags/$tag"
if($LASTEXITCODE -ne 0){ throw 'Tag push failed.' }
$dir='artifacts/phase-snapshots'
New-Item -ItemType Directory -Force -Path $dir | Out-Null
$snapshot=Join-Path $dir ($tag + '.zip')
if(Test-Path $snapshot){ Remove-Item $snapshot -Force }
git archive --format=zip --output=$snapshot $tag
if($LASTEXITCODE -ne 0){ throw 'Snapshot creation failed.' }
$sha=(Get-FileHash $snapshot -Algorithm SHA256).Hash
$remoteLine=(git ls-remote --tags $Remote "refs/tags/$tag^{}").Trim()
if(-not $remoteLine){ $remoteLine=(git ls-remote --tags $Remote "refs/tags/$tag").Trim() }
if(-not $remoteLine){ throw 'Remote tag verification failed.' }
Write-Host "CHECKPOINT PASS"
Write-Host "Commit: $commit"
Write-Host "Tag: $tag"
Write-Host "Snapshot: $snapshot"
Write-Host "SHA256: $sha"
Write-Host 'Record the SHA-256 and remote verification in PROJECT_STATUS.md and RESTORE_POINTS.md in the next authorized documentation commit, or preferably populate them before running via an approved prepare-checkpoint workflow.'
