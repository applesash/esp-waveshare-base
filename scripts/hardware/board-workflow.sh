#!/usr/bin/env bash
set -euo pipefail

usage() {
    printf 'Usage:\n' >&2
    printf '  %s check SKU [PORT]\n' "${0##*/}" >&2
    printf '  %s flash SKU PORT PROJECT_DIR\n' "${0##*/}" >&2
    printf '\nFlash mode requires typing FLASH-SKU after a successful probe.\n' >&2
}

if [[ $# -lt 2 ]]; then
    usage
    exit 2
fi

mode="$1"
sku="$2"
if [[ ! "$sku" =~ ^[0-9]{5}$ ]]; then
    printf 'Invalid SKU: %s\n' "$sku" >&2
    exit 2
fi

repo_root="$(git rev-parse --show-toplevel 2>/dev/null)" || {
    printf 'Run this script from inside the repository.\n' >&2
    exit 1
}
probe="$repo_root/scripts/hardware/probe-esp32.sh"
if [[ ! -x "$probe" ]]; then
    printf 'Probe script is missing or not executable: %s\n' "$probe" >&2
    exit 1
fi

case "$mode" in
    check)
        if [[ $# -gt 3 ]]; then
            usage
            exit 2
        fi
        "$probe" "$sku" "${3:-}"
        ;;
    flash)
        if [[ $# -ne 4 ]]; then
            usage
            exit 2
        fi
        port="$3"
        project_dir="$4"
        if [[ ! -c "$port" ]]; then
            printf 'Serial device is not available: %s\n' "$port" >&2
            exit 1
        fi
        if [[ ! -f "$project_dir/CMakeLists.txt" ]]; then
            printf 'ESP-IDF project is missing CMakeLists.txt: %s\n' "$project_dir" >&2
            exit 1
        fi
        command -v idf.py >/dev/null 2>&1 || {
            printf 'idf.py is required for flash mode.\n' >&2
            exit 1
        }
        "$probe" "$sku" "$port"
        printf 'Probe passed. Registered SKU/MAC identity match verified; proceeding only after explicit confirmation.\n'
        printf 'Type FLASH-%s to build and flash this user-selected board: ' "$sku"
        read -r confirmation
        if [[ "$confirmation" != "FLASH-$sku" ]]; then
            printf 'Flash cancelled; no firmware was written.\n' >&2
            exit 1
        fi
        idf.py -C "$project_dir" -p "$port" build flash
        ;;
    *)
        printf 'Unknown mode: %s\n' "$mode" >&2
        usage
        exit 2
        ;;
esac
