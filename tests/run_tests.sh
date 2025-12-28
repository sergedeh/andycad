#!/bin/sh
set -e
DIR="$(dirname "$0")"
cd "$DIR"
g++ -std=c++17 primitives_test.cpp -I.. -I./gtest -o primitives_test
./primitives_test
