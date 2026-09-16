#!/usr/bin/env sh
set -eu
for c in git python cmake ninja idf.py; do command -v "$c" >/dev/null 2>&1 || { echo "FAIL $c"; exit 1; }; "$c" --version | head -n 1; done
[ -n "${IDF_PATH:-}" ] || { echo 'FAIL IDF_PATH'; exit 1; }
case "$PWD" in *' '*) echo 'FAIL workspace path contains spaces'; exit 1;; esac
echo 'PASS mandatory workspace checks'
