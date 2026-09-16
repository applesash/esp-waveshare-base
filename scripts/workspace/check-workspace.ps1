$ErrorActionPreference = 'Stop'
$checks = @(
  @{Name='git'; Cmd='git'; Args='--version'},
  @{Name='gh'; Cmd='gh'; Args='--version'},
  @{Name='python'; Cmd='python'; Args='--version'},
  @{Name='cmake'; Cmd='cmake'; Args='--version'},
  @{Name='ninja'; Cmd='ninja'; Args='--version'},
  @{Name='idf.py'; Cmd='idf.py'; Args='--version'}
)
$failed=$false
foreach($c in $checks){
  try { $v=& $c.Cmd $c.Args 2>&1 | Select-Object -First 1; Write-Host "PASS $($c.Name): $v" }
  catch { Write-Host "FAIL $($c.Name)"; $failed=$true }
}
if($env:IDF_PATH){ Write-Host "PASS IDF_PATH: $env:IDF_PATH" } else { Write-Host 'FAIL IDF_PATH is not set'; $failed=$true }
if((Get-Location).Path -match ' '){ Write-Host 'FAIL workspace path contains spaces'; $failed=$true } else { Write-Host 'PASS workspace path has no spaces' }
if($failed){ exit 1 }
Write-Host 'PASS mandatory workspace checks'
