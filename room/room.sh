#!/bin/bash

mkdir objectfile

g++ -std=c++17 -c main.cpp -o objectfile/main.cpp.o
g++ -std=c++17 -c shader.cpp -o objectfile/shader.cpp.o
g++ -std=c++17 -c parser.cpp -o objectfile/parser.cpp.o
g++ -std=c++17 -c window.cpp -o objectfile/window.cpp.o
g++ -std=c++17 -c movement.cpp -o objectfile/movement.cpp.o
g++ -std=c++17 -c cube.cpp -o objectfile/cube.cpp.o
g++ -std=c++17 objectfile/*.cpp.o -lGL -lglfw -lX11 -lpthread -ldl -lGLEW -lSOIL -no-pie -o room

rm -r objectfile

./room
