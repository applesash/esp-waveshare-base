#!/usr/bin/env bash
set -euo pipefail

usage() {
    printf 'Usage: %s [SKU] [PORT]\n' "${0##*/}" >&2
    printf 'Example: %s 28154 /dev/ttyACM0\n' "${0##*/}" >&2
}

if [[ $# -gt 2 ]]; then
    usage
    exit 2
fi

sku="${1:-unknown}"
port="${2:-}"
if [[ "$sku" != unknown && ! "$sku" =~ ^[0-9]{5}$ ]]; then
    printf 'Invalid SKU: %s (expected five digits)\n' "$sku" >&2
    exit 2
fi
if ! command -v python >/dev/null 2>&1; then
    printf 'Python is required.\n' >&2
    exit 1
fi
if ! python -m esptool version >/dev/null 2>&1; then
    printf 'Python esptool module is required.\n' >&2
    exit 1
fi

if [[ -z "$port" ]]; then
    shopt -s nullglob
    ports=(/dev/ttyACM* /dev/ttyUSB*)
    shopt -u nullglob
    if [[ ${#ports[@]} -eq 0 ]]; then
        printf 'No /dev/ttyACM* or /dev/ttyUSB* device found.\n' >&2
        exit 1
    fi
    if [[ ${#ports[@]} -ne 1 ]]; then
        printf 'Multiple serial devices found; pass the port explicitly:\n' >&2
        printf '  %s\n' "${ports[@]}" >&2
        exit 1
    fi
    port="${ports[0]}"
fi
if [[ ! -c "$port" ]]; then
    printf 'Serial device is not available: %s\n' "$port" >&2
    exit 1
fi

stamp="$(date +%Y-%m-%d_%H%M%S)"
if [[ "$sku" != unknown && -d "docs/devices/$sku" ]]; then
    mkdir -p "docs/devices/$sku/evidence"
    output="docs/devices/$sku/evidence/PHYSICAL_VALIDATION_${stamp}.md"
else
    mkdir -p artifacts/hardware-probes
    output="artifacts/hardware-probes/probe-${stamp}.md"
fi

chip_output="$(python -m esptool --port "$port" chip_id 2>&1)" || {
    printf '%s\n' "$chip_output" >&2
    printf 'ESP32 chip probe failed for %s.\n' "$port" >&2
    exit 1
}
flash_output="$(python -m esptool --port "$port" flash_id 2>&1)" || {
    printf '%s\n' "$flash_output" >&2
    printf 'ESP32 flash probe failed for %s.\n' "$port" >&2
    exit 1
}
usb_output="$(lsusb 2>/dev/null | grep -i -E 'Espressif|303a:' || true)"

{
    printf '# ESP32 Probe: %s\n\n' "$stamp"
    printf '## Probe metadata\n\n'
    printf -- '- Requested SKU: `%s`\n' "$sku"
    printf -- '- Serial port: `%s`\n' "$port"
    printf -- '- Probe type: read-only chip and flash identity; no erase or firmware write\n'
    printf -- '- USB descriptor: `%s`\n\n' "${usb_output:-not reported}"
    printf '## Chip probe\n\n```text\n%s\n```\n\n' "$chip_output"
    printf '## Flash probe\n\n```text\n%s\n```\n\n' "$flash_output"
    printf '## Interpretation\n\n'
    printf -- '- USB/chip/flash connection: PASS\n'
    printf -- '- Exact Waveshare SKU: requires user identification or board-specific evidence\n'
    printf -- '- Display, touch, GPIO, bus, relay, and power-cycle behavior: NOT TESTED by this probe\n'
} > "$output"

printf 'PROBE PASS\n'
printf 'Port: %s\n' "$port"
printf 'Evidence: %s\n' "$output"
