# Recovery Policy

## Principles

- Published phase tags are immutable.
- Never force-push or move a checkpoint tag.
- Recover by creating a new branch from a verified tag.
- Verify tag, commit, evidence, and snapshot checksum before recovery.

## Inspect latest checkpoint on Linux

```bash
scripts/github/verify-phase-closeout.sh PHASE-02 origin
```

The verifier accepts any completed phase in the `PHASE-XX` format and checks the local annotated tag, remote tag identity, snapshot archive, checksum, and recorded status entries.

## Inspect latest checkpoint on Windows

```powershell
.\scripts\github\verify-recovery.ps1
```


## Create a recovery branch

```powershell
git fetch origin --tags
git switch -c recovery/phase-05 phase-05-complete
```

Do not reset a shared branch unless the owner explicitly authorizes it and repository policy permits it.
