#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="${SCRIPT_DIR}/.."
BUILD_DIR="${SCRIPT_DIR}/build"

if ! command -v emcmake >/dev/null 2>&1; then
  echo "emcmake not found. Please activate Emscripten SDK (emsdk) first." >&2
  exit 1
fi

mkdir -p "${BUILD_DIR}"

emcmake cmake -S "${ROOT_DIR}" -B "${BUILD_DIR}" \
  -DCMAKE_BUILD_TYPE=Release \
  -DANDYCAD_WASM=ON

cmake --build "${BUILD_DIR}" -j "$(nproc)"
