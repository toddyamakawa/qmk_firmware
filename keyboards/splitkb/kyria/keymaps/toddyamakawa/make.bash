#!/usr/bin/env bash
#qmk_bin=$HOME/.local/bin
#export PATH="$PATH:$qmk_bin"
which qmk || exit $?

qmk_firmware="$HOME/qmk_firmware"

keymap='toddyamakawa'
#keymap='default'
build="$qmk_firmware/.build"

qmk compile -kb splitkb/kyria -km "$keymap" || exit $?
#qmk compile -kb kyria -km default

#hexfile="$build/kyria_rev1_$keymap.hex"
hexfile="$build/splitkb_kyria_rev1_$keymap.hex"
dest="$HOME/.config/links/downloads"

echo
echo "\$ cp "$hexfile" "$dest""
cp "$hexfile" "$dest"

