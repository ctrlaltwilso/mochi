#!/usr/bin/env bash
# Clean build, then report any compiler warnings
# Exits non-zero if the build fails or anything warns, so "silent + exit 0" means clean
set -euo pipefail
cd "$(dirname "$0")/.."

pio run -t clean > /dev/null

if output=$(pio run 2>&1); then
  build_ok=true
else
  build_ok=false
fi

if [ "$build_ok" = false ]; then
  echo "$output"
  echo "Build failed"
  exit 1
fi

warnings=$(grep -i "warning:" <<< "$output" || true)

if [ -n "$warnings" ]; then
  echo "$warnings"
  echo "Build succeeded with warnings"
  exit 1
fi

echo "Build succeeded, no warnings"
