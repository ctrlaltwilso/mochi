#!/usr/bin/env bash
# Turn every PNG in assets/ into a C header in src/
# Data is const so it stays in flash and is private to each file that includes it
#   assets/cloud-eye.png -> src/cloud_eye_png.h (variable: cloud_eye_png)
# Requires xxd (preinstalled on macOS and most Linux distros)
set -euo pipefail
cd "$(dirname "$0")/.."

for png in assets/*.png; do
  name=$(basename "$png" .png | tr '-' '_')_png
  echo "#pragma once" > "src/$name.h"
  xxd -i -n "$name" "$png" | sed 's/^unsigned/const unsigned/' >> "src/$name.h"
  echo "$png -> src/$name.h"
done
