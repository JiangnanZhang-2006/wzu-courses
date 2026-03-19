#!/bin/bash
# 用三组数据测试 3578.cpp
cd "$(dirname "$0")"
g++ -o 3578 3578.cpp || exit 1

run_one() {
  local name="$1"
  local dir="$2"
  local id="$3"
  echo "===== $name ($dir) ====="
  ./3578 < "$dir/${id}_input.txt" > /tmp/3578_out.txt 2>&1
  if diff -q "$dir/${id}_output.txt" /tmp/3578_out.txt > /dev/null; then
    echo "通过"
  else
    echo "未通过 (diff 前 30 行):"
    diff -u "$dir/${id}_output.txt" /tmp/3578_out.txt | head -30
  fi
  echo ""
}

run_one "13123" "tmpyfuLVq" "13123"
run_one "13124" "tmp4ZvT0L" "13124"
run_one "13125" "tmpY2rCUC" "13125"
