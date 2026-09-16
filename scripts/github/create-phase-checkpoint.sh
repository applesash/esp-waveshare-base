#!/usr/bin/env bash
set -euo pipefail

usage() {
    printf 'Usage: %s PHASE-XX "Phase Name" [remote]\n' "${0##*/}" >&2
    printf 'Example: %s PHASE-03 "Serial Storage" origin\n' "${0##*/}" >&2
}

if [[ $# -lt 2 || $# -gt 3 ]]; then
    usage
    exit 2
fi

phase="$1"
phase_name="$2"
remote="${3:-origin}"
if [[ ! "$phase" =~ ^PHASE-[0-9]{2}$ ]]; then
    printf 'Invalid phase: %s (expected PHASE-XX)\n' "$phase" >&2
    exit 2
fi
if [[ -z "$phase_name" ]]; then
    printf 'Phase name must not be empty.\n' >&2
    exit 2
fi
if [[ ! -d .git ]]; then
    printf 'Not a Git repository. Run from the repository root.\n' >&2
    exit 1
fi

phase_file="$(find docs/phases -maxdepth 1 -type f -name "${phase//-/_}_*.md" -print -quit)"
if [[ -z "$phase_file" ]]; then
    printf 'No phase document found for %s\n' "$phase" >&2
    exit 1
fi
if git status --porcelain | grep -Eq '^(UU|AA|DD)'; then
    printf 'Unresolved Git conflicts exist.\n' >&2
    exit 1
fi
if ! git remote get-url "$remote" >/dev/null 2>&1; then
    printf 'Remote missing: %s\n' "$remote" >&2
    exit 1
fi
remote_url="$(git remote get-url "$remote")"
if [[ "$remote_url" != https://* ]]; then
    printf 'Remote must use HTTPS: %s\n' "$remote_url" >&2
    exit 1
fi
if command -v gh >/dev/null 2>&1 && ! gh auth status >/dev/null 2>&1; then
    printf 'GitHub authentication unavailable.\n' >&2
    exit 1
fi

tag="${phase,,}-complete"
if git tag --list "$tag" | grep -Fxq "$tag"; then
    printf 'Local tag already exists and is immutable: %s\n' "$tag" >&2
    exit 1
fi
if [[ -n "$(git ls-remote --tags "$remote" "refs/tags/$tag" 2>/dev/null)" ]]; then
    printf 'Remote tag already exists and is immutable: %s\n' "$tag" >&2
    exit 1
fi

printf 'Required tests, evidence, traceability, PROJECT_STATUS.md, and RESTORE_POINTS.md must already be updated.\n'
printf 'Type GATE-PASSED to create and publish %s: ' "$tag"
read -r confirmation
if [[ "$confirmation" != GATE-PASSED ]]; then
    printf 'Checkpoint cancelled.\n' >&2
    exit 1
fi

git add --all
forbidden="$(git diff --cached --name-only | grep -E '(^|/)(\.env|.*\.pem|.*\.key|sdkconfig|build/|node_modules/)' || true)"
if [[ -n "$forbidden" ]]; then
    printf 'Potential secret/generated files staged:\n%s\n' "$forbidden" >&2
    exit 1
fi

git commit -m "[$phase] $phase_name - Gate Passed"
commit="$(git rev-parse HEAD)"
git tag -a "$tag" -m "$phase $phase_name - Gate Passed" "$commit"
branch="$(git branch --show-current)"
if [[ -z "$branch" ]]; then
    printf 'Detached HEAD is not allowed for checkpoint publishing.\n' >&2
    exit 1
fi

git push -u "$remote" "$branch"
git push "$remote" "refs/tags/$tag"

snapshot_dir="artifacts/phase-snapshots"
snapshot="$snapshot_dir/$tag.zip"
mkdir -p "$snapshot_dir"
git archive --format=zip --output="$snapshot" "$tag"
sha256="$(sha256sum "$snapshot" | awk '{ print $1 }')"
remote_commit="$(git ls-remote --tags "$remote" "refs/tags/${tag}^{}" | awk 'NR == 1 { print $1 }')"
if [[ -z "$remote_commit" || "$remote_commit" != "$commit" ]]; then
    printf 'Remote tag verification failed.\n' >&2
    exit 1
fi

printf 'CHECKPOINT PASS\n'
printf 'Commit: %s\n' "$commit"
printf 'Tag: %s\n' "$tag"
printf 'Snapshot: %s\n' "$snapshot"
printf 'SHA256: %s\n' "$sha256"
printf 'Update PROJECT_STATUS.md and docs/recovery/RESTORE_POINTS.md, commit those records, then run verify-phase-closeout.sh.\n'
