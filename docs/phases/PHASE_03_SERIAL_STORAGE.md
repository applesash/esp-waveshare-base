# PHASE-03: Serial Storage

## Purpose
Validate flash/monitor, memory configuration, partitions, NVS, and SD diagnostics.

## Inputs
- AGENT_CONTRACT.md
- PROJECT_STATUS.md
- Applicable requirements, manifests, ADRs, and evidence

## Gate rule
Do not enter this phase unless the prior mandatory gate passed. Do not leave until implementation, required tests, documentation, traceability, simulation, and applicable physical evidence pass.

## Applicable SKU Validation

SD, serial, memory, partition, and NVS behavior shall be implemented and physically validated independently on SKU 28154, SKU 28141, and SKU 30838 before phase closeout. A passing result on one board or board instance shall not satisfy another SKU. A board-instance defect shall be recorded by stable identity, while the phase remains blocked until another physically available instance of that SKU passes or an owner-approved exception is documented.

## BSP Promotion And Evidence Retention

Before phase closeout, promote each source-backed and physically validated board initialization sequence into the applicable exact-SKU BSP. Expose only a neutral, provider-facing board API; applications and diagnostics shall not retain reusable GPIO, bus, expander, driver, or filesystem initialization logic. Keep diagnostic probes, captured logs, source-register entries, and physical-validation evidence in place as immutable learning records. Record board-instance-specific outcomes by MAC or other stable identity without generalizing a physical defect to every board of the SKU.

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
5. Run `scripts/github/create-phase-checkpoint.sh PHASE-03 "Serial Storage" origin` to create the commit, immutable tag, remote push, and snapshot.
9. Run `scripts/github/verify-phase-closeout.sh PHASE-03 origin` on Linux to verify tag identity, commit reachability, snapshot SHA-256, and recorded evidence.
10. Close the phase only after the verifier passes.
