# Agent Startup Procedure

1. Read `AGENT_CONTRACT.md` completely and confirm Version 3.1.0.
2. Read `PROJECT_STATUS.md`.
3. Read the current file under `docs/phases/`.
4. Read `TRACEABILITY_MATRIX.md`.
5. Read `dependencies.lock`.
6. Read applicable board manifest and exact-SKU evidence.
7. Read applicable accepted ADRs.
8. Inspect existing source and Git status before generating anything.
9. Determine the latest completed phase, local tag, matching remote tag, commit, validation report, snapshot, and checksum. Run `scripts/github/verify-recovery.ps1` when a checkpoint exists.
10. Detect the host OS before running repo scripts. On Linux/macOS, prefer the `.sh` entry points; on Windows, prefer the `.ps1` or `.cmd` entry points. Use the matching script type for the active environment and do not invoke a script from a different OS family unless there is an explicit, documented exception.
11. State current phase, board, build mode, requirements, expected file changes, tests, assumptions, and unknowns.
12. Work only within the current authorization boundary and modify the smallest necessary file set.
13. Run required tests and update status, traceability, evidence, and changelog.
14. Never claim physical validation unless the exact hardware test was run and recorded.
15. Stop at a failed gate.

## Permanent prohibitions

- No guessed GPIO, RGB timing, expander mapping, bus mapping, or safe state.
- No code copied from another SKU.
- No Arduino, Wire, TFT_eSPI, LovyanGFX, lvgl_esp32_drivers, unofficial GT911, random forum, or untraceable code.
- No UI business/operational logic.
- No duplicate Web and LVGL workflows or screen models.
- No credentials, tokens, private keys, passwords, or MFA data in source, scripts, logs, fixtures, documentation, or chat.
- No silent SDK, dependency, architecture, partition, or security change.

## Mandatory successful phase closeout

1. Pass all required tests and gate checks.
2. Record validation evidence and acceptance report.
3. Update traceability, status, changelog, and restore-point index.
4. Run the checkpoint script from the repository root.
5. Verify the commit and immutable annotated tag exist locally and remotely.
6. Verify the local snapshot checksum.
7. Do not begin the next phase until recovery verification passes.
