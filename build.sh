#!/bin/bash

g++ -c *.cpp -std=c++11
g++ *.o -o Neckbeard1v1 -lsfml-window -lsfml-network -lsfml-graphics -lsfml-system
rm *.o
