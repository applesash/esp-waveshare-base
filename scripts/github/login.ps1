$ErrorActionPreference='Stop'
try { gh auth status; Write-Host 'GitHub authentication already available.'; exit 0 } catch {}
Write-Host 'A trusted GitHub browser/device authentication flow will open.'
Write-Host 'Complete credentials and MFA only in the trusted GitHub/identity-provider prompt.'
gh auth login --git-protocol https --web
if($LASTEXITCODE -ne 0){ exit $LASTEXITCODE }
gh auth setup-git
gh auth status
