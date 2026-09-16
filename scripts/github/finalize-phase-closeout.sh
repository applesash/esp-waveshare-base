#!/usr/bin/env bash
set -euo pipefail

usage() {
    printf 'Usage: %s PHASE-XX "Gate Label" [remote]\n' "${0##*/}" >&2
    printf 'Example: %s PHASE-02 "SOURCE EVIDENCE VERIFIED" origin\n' "${0##*/}" >&2
}

if [[ $# -lt 2 || $# -gt 3 ]]; then
    usage
    exit 2
fi

phase="$1"
gate="$2"
remote="${3:-origin}"
if [[ ! "$phase" =~ ^PHASE-[0-9]{2}$ || -z "$gate" ]]; then
    printf 'Invalid phase or gate label.\n' >&2
    exit 2
fi
if [[ ! -d .git ]]; then
    printf 'Not a Git repository. Run from the repository root.\n' >&2
    exit 1
fi
if [[ -n "$(git status --porcelain)" ]]; then
    printf 'Working tree must be clean before finalization.\n' >&2
    exit 1
fi

tag="${phase,,}-complete"
status_file="PROJECT_STATUS.md"
restore_file="docs/recovery/RESTORE_POINTS.md"
snapshot="artifacts/phase-snapshots/${tag}.zip"
if ! git rev-parse --verify --quiet "refs/tags/$tag" >/dev/null; then
    printf 'Local tag missing: %s\n' "$tag" >&2
    exit 1
fi
if [[ "$(git cat-file -t "$(git rev-parse "refs/tags/$tag")")" != tag ]]; then
    printf 'Tag is not annotated: %s\n' "$tag" >&2
    exit 1
fi
if ! git remote get-url "$remote" >/dev/null 2>&1; then
    printf 'Remote missing: %s\n' "$remote" >&2
    exit 1
fi
commit="$(git rev-list -n 1 "$tag")"
remote_commit="$(git ls-remote --tags "$remote" "refs/tags/${tag}^{}" | awk 'NR == 1 { print $1 }')"
if [[ "$remote_commit" != "$commit" ]]; then
    printf 'Remote tag does not match local checkpoint.\n' >&2
    exit 1
fi
if [[ ! -f "$snapshot" ]]; then
    printf 'Snapshot missing: %s\n' "$snapshot" >&2
    exit 1
fi
sha256="$(sha256sum "$snapshot" | awk '{ print $1 }')"
date_value="$(date +%F)"
phase_label="Phase-${phase#PHASE-}"
restore_line="| $phase | $gate | $commit | $tag | YES | $snapshot | $sha256 | scripts/github/verify-phase-closeout.sh | $date_value |"

sed -i \
    -e "s/^- Completed phase: .*/- Completed phase: $phase/" \
    -e "s/^- Git commit: .*/- Git commit: $commit/" \
    -e "s/^- Git tag: .*/- Git tag: $tag/" \
    -e "s/^- Push status: .*/- Push status: VERIFIED on $remote/" \
    -e "s#^- Snapshot package: .*#- Snapshot package: $snapshot#" \
    -e "s/^- Snapshot SHA-256: .*/- Snapshot SHA-256: $sha256/" \
    -e "s/^- Validation status: .*/- Validation status: PASS (checkpoint + remote recovery verification)/" \
    -e "s/^- Remote verification: .*/- Remote verification: VERIFIED/" \
    -e "s/^- ${phase_label} source validation: .*/- ${phase_label} source validation: COMPLETE/" \
    "$status_file"

awk -v phase="$phase" -v restore_line="$restore_line" \
    'index($0, "| " phase " |") == 1 { print restore_line; next } { print }' \
    "$restore_file" > "$restore_file.tmp"
mv "$restore_file.tmp" "$restore_file"

git diff --check
git add "$status_file" "$restore_file"
if git diff --cached --quiet; then
    printf 'Closeout records already up to date for %s.\n' "$phase"
else
    git commit -m "[$phase] Record final closeout verification"
    branch="$(git branch --show-current)"
    if [[ -z "$branch" ]]; then
        printf 'Detached HEAD is not allowed for publishing.\n' >&2
        exit 1
    fi
    git push "$remote" "$branch"
fi

scripts/github/verify-phase-closeout.sh "$phase" "$remote"
