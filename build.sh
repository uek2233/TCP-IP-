#!/usr/bin/env bash
set -euo pipefail

cd "$(dirname "$0")"

if [[ ! -f .tools ]]; then
  echo "Error: .tools not found in $(pwd)"
  exit 1
fi

source .tools

BUILD_DIR=build
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

cmake -DCMAKE_C_COMPILER="${CC}" -DCMAKE_C_FLAGS="${CFLAGS}" -DCMAKE_BUILD_TYPE=Release ..
cmake --build . -- -j "$(nproc)"

echo "Build completed. Binaries are in: ${PWD}/bin"
