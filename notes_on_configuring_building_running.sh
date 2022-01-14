#!/bin/bash

# Assuming that
#  1. Your current working directory is the directory containing this file
#  2. You have the deutex tool on your PATH (the version of deutex this was
#     tested with was built from the related github repo:
#     https://github.com/Doom-Utils/deutex, at commit ef1c06a from Jan 3, 2021)
#  3. You have a copy of the shareware doom WAD in the folder at the path ~/Document
#
# Then this script performs all the configuration and building necessary
# to produce an executable copy of prdoom, and then runs it.

# Copy the shareware WAD into the data directory
cp ~/Documents/doom1.wad data/

# Run the bootstrap script, which creates a 'configure' script
./bootstrap

# Run the configure script, which generates Makefiles, among other things
./configure

# Run make, which produces an executable, among other things
make

# Run the game, from a working directory that contains the WAD files
cd data/
../src/prboom
