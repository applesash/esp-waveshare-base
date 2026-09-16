# Phase 18 First Real Application

## Purpose
Build the first application-specific module using validated platform capabilities.

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
5. Create a checkpoint commit using `[PHASE-XX] <Phase Name> - Gate Passed`.
6. Create immutable annotated tag `phase-XX-complete`.
7. Push the phase branch and tag over HTTPS without force.
8. Generate `artifacts/phase-snapshots/phase-XX-complete.zip` from the tag.
9. Verify local and remote tag identity, commit reachability, snapshot SHA-256, and evidence.
10. Close the phase only after recovery verification passes.
