#!/bin/bash

touch fsdata
rm fsdata
rm -rf out
make LOCAL=1
cp -r out/FSROOT/* ~/Repos/FSROOT/DATA/
cp -r out/FSROOTSTRN/* ~/Repos/FSROOT/STRN/
cp -r out/FSROOTBGM/* ~/Repos/FSROOT/SOUND/BGM/

