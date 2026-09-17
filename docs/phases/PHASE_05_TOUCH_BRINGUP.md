# PHASE-05: Touch Bringup

## Purpose
Validate raw GT911 independently of LVGL.

## Inputs
- AGENT_CONTRACT.md
- PROJECT_STATUS.md
- Applicable requirements, manifests, ADRs, and evidence

## Gate rule
Do not enter this phase unless the prior mandatory gate passed. Do not leave until implementation, required tests, documentation, traceability, simulation, and applicable physical evidence pass.

## Applicable SKU Validation

Raw touch identification, event reception, coordinate range, and transform behavior shall be implemented and physically validated independently on SKU 28154 and SKU 28141 before phase closeout. SKU 30838 has no touch capability and is excluded only because its capability matrix records the block as not present. A passing result on one touch SKU or board instance shall not satisfy the other.

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
5. Run `scripts/github/create-phase-checkpoint.sh PHASE-05 "Touch Bringup" origin` to create the commit, immutable tag, remote push, and snapshot.
9. Run `scripts/github/verify-phase-closeout.sh PHASE-05 origin` on Linux to verify tag identity, commit reachability, snapshot SHA-256, and recorded evidence.
10. Close the phase only after the verifier passes.
