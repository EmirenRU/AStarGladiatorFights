cmake_minimum_required(VERSION 3.22)
project(Lab02_Emil)

set(CMAKE_CXX_STANDARD 20)

add_executable(Lab02_Emil src/main/main.cpp src/Map/Map.cpp src/Map/Map.h src/Node/Node.h src/Units/Player.h src/Units/Knight.cpp src/Units/Knight.h src/Units/Archer.cpp src/Units/Archer.h src/main/Event.h)
