# PHASE-05: Touch Bringup

## Purpose
Validate raw GT911 independently of LVGL.

## Inputs
- AGENT_CONTRACT.md
- PROJECT_STATUS.md
- Applicable requirements, manifests, ADRs, and evidence

## Gate rule
Do not enter this phase unless the prior mandatory gate passed. Do not leave until implementation, required tests, documentation, traceability, simulation, and applicable physical evidence pass.

## Required report
- Requirements covered
- Files changed
- Tests executed and results
- Evidence created
- Unknowns and limitations
- Next permitted phase

## Mandatory phase closeout

1. Pass all required acceptance tests.
2. Record validation evidence and phase acceptance report.
3. Update `TRACEABILITY_MATRIX.md`, `PROJECT_STATUS.md`, `CHANGELOG.md` when applicable, and `docs/recovery/RESTORE_POINTS.md`.
4. Ensure no secrets, build caches, or unapproved artifacts are staged.
5. Run `scripts/github/create-phase-checkpoint.sh PHASE-05 "Touch Bringup" origin` to create the commit, immutable tag, remote push, and snapshot.
9. Run `scripts/github/verify-phase-closeout.sh PHASE-05 origin` on Linux to verify tag identity, commit reachability, snapshot SHA-256, and recorded evidence.
10. Close the phase only after the verifier passes.
