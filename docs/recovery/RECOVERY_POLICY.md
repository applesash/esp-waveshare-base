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

## Create a checkpoint on Linux

```bash
scripts/github/create-phase-checkpoint.sh PHASE-03 "Serial Storage" origin
```

The checkpoint script requires the explicit `GATE-PASSED` confirmation, refuses conflicts, missing HTTPS remotes, reused tags, and staged secret/generated files, then commits, tags, pushes, archives, and performs initial remote verification. Run `verify-phase-closeout.sh` after recording the resulting checksum.

## Finalize a checkpoint on Linux

```bash
scripts/github/finalize-phase-closeout.sh PHASE-03 "SOURCE EVIDENCE VERIFIED" origin
```

This records the immutable tag commit, remote status, snapshot path, checksum, and validation result in the project status and restore-point files, publishes that documentation commit, and reruns the verifier.

Exact-board physical validation is documented in [PHYSICAL_VALIDATION_RUNBOOK.md](PHYSICAL_VALIDATION_RUNBOOK.md).


## Create a recovery branch

```powershell
git fetch origin --tags
git switch -c recovery/phase-05 phase-05-complete
```

Do not reset a shared branch unless the owner explicitly authorizes it and repository policy permits it.
