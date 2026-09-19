#!/usr/bin/env bash
set -e

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"

cmake --preset build-arm -S "$PROJECT_ROOT"
cmake --build --preset build-arm
