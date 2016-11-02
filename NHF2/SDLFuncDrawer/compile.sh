#!/bin/bash
g++ -Wall -o SDLFuncDrawer *.cpp `sdl-config --cflags --libs` -lGL -lGLU

