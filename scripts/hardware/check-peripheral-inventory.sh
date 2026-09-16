#!/usr/bin/env bash
set -euo pipefail

usage() {
    printf 'Usage: %s SKU\n' "${0##*/}" >&2
    printf 'Example: %s 28154\n' "${0##*/}" >&2
}

if [[ $# -ne 1 || ! "$1" =~ ^[0-9]{5}$ ]]; then
    usage
    exit 2
fi

sku="$1"
base="docs/devices/$sku"
capability="$base/CAPABILITY_MATRIX.md"
gpio="$base/GPIO_REGISTER.md"
source_register="$base/SOURCE_REGISTER.md"
for file in "$capability" "$gpio" "$source_register"; do
    [[ -f "$file" ]] || { printf 'Missing inventory file: %s\n' "$file" >&2; exit 1; }
done

combined="$(cat "$capability" "$gpio" "$source_register")"
failed=0
check_category() {
    local label="$1"
    local pattern="$2"
    if printf '%s\n' "$combined" | grep -Eiq "$pattern"; then
        printf 'PASS %-16s\n' "$label"
    else
        printf 'FAIL %-16s missing from SKU %s inventory\n' "$label" "$sku"
        failed=1
    fi
}

check_category display 'display|lcd|st7701'
check_category touch 'touch|gt911'
check_category i2c 'i2c|sda|scl'
check_category rs485 'rs485|sp3485'
check_category can 'can|twai|tja1051'
check_category storage 'sd|micro.?sd|storage'
check_category rtc 'rtc|pcf85063'
check_category audio 'buzzer|speaker|bee'
check_category backlight 'backlight|led'
check_category power 'battery|power|vin|reset'
check_category network 'wifi|bluetooth|ethernet'
check_category usb 'usb'
check_category gpio 'gpio|exio|io_expander|helper'

if [[ "$failed" -ne 0 ]]; then
    printf 'PERIPHERAL INVENTORY FAIL: complete source-backed records for SKU %s.\n' "$sku" >&2
    exit 1
fi
printf 'PERIPHERAL INVENTORY PASS: SKU %s categories covered.\n' "$sku"
