# Recovery Policy

## Principles

- Published phase tags are immutable.
- Never force-push or move a checkpoint tag.
- Recover by creating a new branch from a verified tag.
- Verify tag, commit, evidence, and snapshot checksum before recovery.

## Inspect latest checkpoint

```powershell
.\scripts\github\verify-recovery.ps1
```

On Linux, use the repository-native verifier:

```bash
scripts/github/verify-phase-closeout.sh PHASE-02 origin
```

## Create a recovery branch

```powershell
git fetch origin --tags
git switch -c recovery/phase-05 phase-05-complete
```

Do not reset a shared branch unless the owner explicitly authorizes it and repository policy permits it.
