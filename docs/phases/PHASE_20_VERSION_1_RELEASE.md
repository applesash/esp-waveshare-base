# Phase 20 Version 1 Release

## Purpose
Complete Production validation and publish the approved 1.0.0 release.

## Inputs
- Passed prior phase checkpoint
- Contract, status, traceability, ADRs, and applicable evidence

## Gate rule
Do not enter unless the prior checkpoint is verified locally and remotely.

## Mandatory phase closeout

1. Pass all required acceptance tests.
2. Record validation evidence and phase acceptance report.
3. Update `TRACEABILITY_MATRIX.md`, `PROJECT_STATUS.md`, `CHANGELOG.md` when applicable, and `docs/recovery/RESTORE_POINTS.md`.
4. Ensure no secrets, build caches, or unapproved artifacts are staged.
5. Run `scripts/github/create-phase-checkpoint.sh PHASE-20 "Version 1 Release" origin` to create the commit, immutable tag, remote push, and snapshot.
9. Run `scripts/github/verify-phase-closeout.sh PHASE-20 origin` on Linux to verify tag identity, commit reachability, snapshot SHA-256, and recorded evidence.
10. Close the phase only after the verifier passes.
