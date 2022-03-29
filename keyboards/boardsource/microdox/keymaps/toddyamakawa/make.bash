#!/usr/bin/env bash
#qmk_bin=$HOME/.local/bin
#export PATH="$PATH:$qmk_bin"
which qmk || exit $?

keymap='toddyamakawa'
#keymap='default'

qmk compile -kb boardsource/microdox -km "$keymap" || exit $?

top="$(git top 2>/dev/null)"
build="$top/.build"
hexfile="$build/boardsource_microdox_$keymap.hex"
dest="$HOME/.config/links/downloads"
[[ -d "$HOME/Downloads" ]] && dest="$HOME/Downloads"

echo
echo "\$ cp "$hexfile" "$dest""
cp "$hexfile" "$dest"

