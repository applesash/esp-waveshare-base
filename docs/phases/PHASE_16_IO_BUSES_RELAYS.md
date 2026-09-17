# PHASE-16: Io Buses Relays

## Purpose
Implement all verified board capabilities safely.

## Inputs
- AGENT_CONTRACT.md
- PROJECT_STATUS.md
- Applicable requirements, manifests, ADRs, and evidence

## Gate rule
Do not enter this phase unless the prior mandatory gate passed. Do not leave until implementation, required tests, documentation, traceability, simulation, and applicable physical evidence pass.

## Applicable SKU Validation

Every verified capability shall be implemented and physically validated on every supported SKU that declares the capability before phase closeout. The phase report shall include a per-SKU capability matrix identifying tested board instances, stable identities, evidence paths, and explicitly not-present blocks. Results from one SKU or board instance do not satisfy another; unavailable hardware blocks the applicable capability gate unless an owner-approved exception is documented.

The owner may defer a physical test for an applicable capability only by recording the scope, reason, and deferred validation in the phase report and board evidence. Deferred capabilities remain incomplete and cannot be represented as physically tested.

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
5. Run `scripts/github/create-phase-checkpoint.sh PHASE-16 "IO Buses Relays" origin` to create the commit, immutable tag, remote push, and snapshot.
9. Run `scripts/github/verify-phase-closeout.sh PHASE-16 origin` on Linux to verify tag identity, commit reachability, snapshot SHA-256, and recorded evidence.
10. Close the phase only after the verifier passes.
