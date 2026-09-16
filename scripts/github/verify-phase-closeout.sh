#!/usr/bin/env bash
set -euo pipefail

usage() {
    printf 'Usage: %s PHASE-XX [remote]\n' "${0##*/}" >&2
    printf 'Example: %s PHASE-02 origin\n' "${0##*/}" >&2
}

if [[ $# -lt 1 || $# -gt 2 ]]; then
    usage
    exit 2
fi

phase="$1"
remote="${2:-origin}"
if [[ ! "$phase" =~ ^PHASE-[0-9]{2}$ ]]; then
    printf 'Invalid phase: %s (expected PHASE-XX)\n' "$phase" >&2
    exit 2
fi

if [[ ! -d .git ]]; then
    printf 'Not a Git repository. Run from the repository root.\n' >&2
    exit 1
fi

tag="${phase,,}-complete"
snapshot="artifacts/phase-snapshots/${tag}.zip"
status_file="PROJECT_STATUS.md"
restore_file="docs/recovery/RESTORE_POINTS.md"

if ! git rev-parse --verify --quiet "refs/tags/$tag" >/dev/null; then
    printf 'Local tag missing: %s\n' "$tag" >&2
    exit 1
fi

local_tag_object="$(git rev-parse "refs/tags/$tag")"
if [[ "$(git cat-file -t "$local_tag_object")" != tag ]]; then
    printf 'Tag is not annotated: %s\n' "$tag" >&2
    exit 1
fi

local_commit="$(git rev-list -n 1 "$tag")"
if ! git remote get-url "$remote" >/dev/null 2>&1; then
    printf 'Remote missing: %s\n' "$remote" >&2
    exit 1
fi

remote_commit="$(git ls-remote --tags "$remote" "refs/tags/${tag}^{}" | awk 'NR == 1 { print $1 }')"
if [[ -z "$remote_commit" ]]; then
    remote_commit="$(git ls-remote --tags "$remote" "refs/tags/$tag" | awk 'NR == 1 { print $1 }')"
fi
if [[ -z "$remote_commit" ]]; then
    printf 'Remote tag missing: %s\n' "$tag" >&2
    exit 1
fi
if [[ "$local_commit" != "$remote_commit" ]]; then
    printf 'Tag commit mismatch: local=%s remote=%s\n' "$local_commit" "$remote_commit" >&2
    exit 1
fi

if [[ ! -f "$snapshot" ]]; then
    printf 'Snapshot missing: %s\n' "$snapshot" >&2
    exit 1
fi
sha256="$(sha256sum "$snapshot" | awk '{ print $1 }')"
if ! unzip -tq "$snapshot" >/dev/null; then
    printf 'Snapshot is not a valid ZIP archive: %s\n' "$snapshot" >&2
    exit 1
fi

for file in "$status_file" "$restore_file"; do
    if [[ ! -f "$file" ]]; then
        printf 'Required record missing: %s\n' "$file" >&2
        exit 1
    fi
done

if ! grep -Fq "$tag" "$status_file" || ! grep -Fq "$local_commit" "$status_file" || ! grep -Fq "$sha256" "$status_file"; then
    printf 'PROJECT_STATUS.md does not record tag, commit, and snapshot SHA-256 for %s\n' "$tag" >&2
    exit 1
fi
if ! grep -Fq "$tag" "$restore_file" || ! grep -Fq "$local_commit" "$restore_file" || ! grep -Fq "$sha256" "$restore_file"; then
    printf 'RESTORE_POINTS.md does not record tag, commit, and snapshot SHA-256 for %s\n' "$tag" >&2
    exit 1
fi

printf 'CLOSEOUT VERIFICATION PASS\n'
printf 'Phase: %s\n' "$phase"
printf 'Tag: %s\n' "$tag"
printf 'Commit: %s\n' "$local_commit"
printf 'Remote: %s\n' "$remote"
printf 'Snapshot: %s\n' "$snapshot"
printf 'SHA256: %s\n' "$sha256"
