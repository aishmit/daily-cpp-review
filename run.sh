#!/usr/bin/env bash
# Build + test a day.
#   ./run.sh 001            # systems (C++, ASan+UBSan) and design (Python)
#   ./run.sh 001 sys        # systems only
#   ./run.sh 001 design     # design only
#   SAN=thread ./run.sh 023 # ThreadSanitizer instead (concurrency days)
#   SAN=none   ./run.sh 011 # no sanitizers, -O2 (benchmark days)
set -euo pipefail
cd "$(dirname "$0")"

day="${1:?usage: ./run.sh NNN [sys|design]}"
what="${2:-all}"
dir="days/$day"
[[ -d "$dir" ]] || { echo "no such day: $dir"; exit 1; }

CXX="${CXX:-$(command -v clang++ || command -v g++)}"
SAN="${SAN:-address,undefined}"
status=0

if [[ "$what" != design && -d "$dir/systems" ]]; then
  echo "=== systems ($dir/systems) — $CXX, sanitizers: $SAN ==="
  mkdir -p build
  flags=(-std=c++20 -Wall -Wextra -Wpedantic -g -I common -I "$dir/systems")
  if [[ "$SAN" == none ]]; then flags+=(-O2 -DNDEBUG); else flags+=(-O1 -fno-omit-frame-pointer -fno-builtin "-fsanitize=$SAN"); fi
  for src in "$dir"/systems/drill.cpp "$dir"/systems/test_*.cpp; do
    [[ -e "$src" ]] || continue
    bin="build/day${day}_$(basename "${src%.cpp}")"
    echo "--- $(basename "$src")"
    if "$CXX" "${flags[@]}" "$src" -o "$bin"; then
      # LeakSanitizer isn't supported by Apple clang on macOS; enable it on Linux only.
      if [[ "$(uname)" == Linux ]]; then ASAN_OPTIONS=detect_leaks=1 "$bin" || status=1; else "$bin" || status=1; fi
    else
      echo "    (does not compile yet)"; status=1
    fi
  done
fi

if [[ "$what" != sys && -d "$dir/design" ]]; then
  echo; echo "=== design ($dir/design) ==="
  python3 common/pytest_lite.py "$dir"/design/test_*.py || status=1
fi

exit $status
