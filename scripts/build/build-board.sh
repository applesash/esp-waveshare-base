#!/usr/bin/env bash
set -euo pipefail

usage() {
    printf 'Usage: %s SKU [build|reconfigure]\n' "${0##*/}" >&2
    printf 'Example: %s 28154 build\n' "${0##*/}" >&2
}

if [[ $# -lt 1 || $# -gt 2 ]]; then
    usage
    exit 2
fi

sku="$1"
mode="${2:-build}"
if [[ ! "$sku" =~ ^[0-9]{5}$ ]]; then
    printf 'Invalid SKU: %s\n' "$sku" >&2
    exit 2
fi
if [[ "$mode" != build && "$mode" != reconfigure ]]; then
    printf 'Invalid build mode: %s\n' "$mode" >&2
    exit 2
fi
command -v idf.py >/dev/null 2>&1 || {
    printf 'idf.py is required.\n' >&2
    exit 1
}

registry="scripts/build/board-builds.conf"
if [[ ! -f "$registry" ]]; then
    printf 'Board build registry is missing: %s\n' "$registry" >&2
    exit 1
fi

IFS='|' read -r registered_sku project_dir project_name status < <(awk -F'|' -v requested_sku="$sku" '$1 == requested_sku { print; exit }' "$registry")
if [[ "$registered_sku" != "$sku" ]]; then
    printf 'No board build is registered for SKU %s.\n' "$sku" >&2
    exit 1
fi
if [[ "$status" != IMPLEMENTED ]]; then
    printf 'SKU %s build is not implemented. Registered target: %s\n' "$sku" "$project_name" >&2
    exit 1
fi
if [[ ! -f "$project_dir/CMakeLists.txt" ]]; then
    printf 'SKU %s project is missing: %s\n' "$sku" "$project_dir" >&2
    exit 1
fi

printf 'Building SKU %s (%s) from %s\n' "$sku" "$project_name" "$project_dir"
case "$mode" in
    build)
        idf.py -C "$project_dir" build
        ;;
    reconfigure)
        idf.py -C "$project_dir" set-target esp32s3 build
        ;;
esac
