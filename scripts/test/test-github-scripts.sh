#!/usr/bin/env bash
set -euo pipefail

checkpoint="scripts/github/create-phase-checkpoint.sh"
finalizer="scripts/github/finalize-phase-closeout.sh"
verifier="scripts/github/verify-phase-closeout.sh"

for script in "$checkpoint" "$finalizer" "$verifier"; do
    [[ -x "$script" ]] || { printf 'FAIL not executable: %s\n' "$script" >&2; exit 1; }
    bash -n "$script"
done

before="$(git status --porcelain)"
if "$checkpoint" >/dev/null 2>&1; then
    printf 'FAIL checkpoint accepted missing arguments\n' >&2
    exit 1
fi
if "$finalizer" >/dev/null 2>&1; then
    printf 'FAIL finalizer accepted missing arguments\n' >&2
    exit 1
fi
if "$verifier" PHASE-99 origin >/dev/null 2>&1; then
    printf 'FAIL verifier accepted a missing phase tag\n' >&2
    exit 1
fi
after="$(git status --porcelain)"
[[ "$before" == "$after" ]] || { printf 'FAIL negative tests changed the worktree\n' >&2; exit 1; }
printf 'PASS Linux Git workflow script tests\n'
