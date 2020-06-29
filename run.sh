#!/bin/bash

# Remake out/
rm -rf out/
mkdir out

qcc -Wall -O2 flow.c -o out/flow -L$BASILISK/gl -lglutils -lfb_glx -lGLU -lGLEW -lGL -lX11 -lm
cd out
./flow
vlc HorizontalVelocity.mp4
