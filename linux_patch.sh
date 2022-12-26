#!/bin/sh
echo "----- Starting JVH Linux Patch -----"
cp ./ext/* ./src/
mkdir headers/ext
cp ./ext/* ./headers/ext/
echo "[sh] JVH Patched. Now you can use <make> for compiling the program."
exit 0

