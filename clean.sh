#!/usr/bin/env bash
if [[ -d build ]]; then
  echo "build directory already exists in $(pwd)"
  rm -rf build
  exit 1
fi

