#!/bin/sh
CFLAGS="-Wextra -Wall -std=gnu99 -pedantic -O2"

OUT="$(dirname "$(readlink -f "$0")")"/out
SRC="$(dirname "$(readlink -f "$0")")"/src

mkdir "$OUT" 2> /dev/null
rm -r "${OUT:?}/"* 2> /dev/null

gcc -o "$OUT"/tlf "$SRC"/main.c $CFLAGS 
