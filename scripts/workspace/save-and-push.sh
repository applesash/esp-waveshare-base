#!/usr/bin/env bash
set -euo pipefail

usage() {
    cat <<'EOF'
Usage: save-and-push.sh [--message "commit message"] [--remote origin]

Quick helper to save temporary work and push it to the current branch.

Examples:
  scripts/workspace/save-and-push.sh
  scripts/workspace/save-and-push.sh --message "temp: debug touch bring-up"
  scripts/workspace/save-and-push.sh --remote upstream
EOF
}

message="temp: save work"
remote="origin"

while [[ $# -gt 0 ]]; do
    case "$1" in
        -m|--message)
            if [[ $# -lt 2 ]]; then
                echo "Missing value for $1" >&2
                usage >&2
                exit 2
            fi
            message="$2"
            shift 2
            ;;
        -r|--remote)
            if [[ $# -lt 2 ]]; then
                echo "Missing value for $1" >&2
                usage >&2
                exit 2
            fi
            remote="$2"
            shift 2
            ;;
        -h|--help)
            usage
            exit 0
            ;;
        *)
            echo "Unknown argument: $1" >&2
            usage >&2
            exit 2
            ;;
    esac
done

if ! git rev-parse --show-toplevel >/dev/null 2>&1; then
    echo "Not inside a git repository." >&2
    exit 1
fi

repo_root="$(git rev-parse --show-toplevel)"
cd "$repo_root"

if [[ -z "$(git status --porcelain)" ]]; then
    echo "No local changes to save."
    exit 0
fi

branch="$(git branch --show-current)"
if [[ -z "$branch" ]]; then
    echo "Detached HEAD detected. Check out a branch before saving work." >&2
    exit 1
fi

if ! git remote get-url "$remote" >/dev/null 2>&1; then
    echo "Remote '$remote' does not exist." >&2
    exit 1
fi

git add -A

git commit -m "$message"

git push "$remote" "$branch"

echo "Saved and pushed current work to $remote/$branch"
