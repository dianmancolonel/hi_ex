cmake_minimum_required(VERSION 4.0)
project(hi_ex)

set(CMAKE_CXX_STANDARD 20)

add_executable(hi_ex main.cpp
        biology/src/Game.cpp
        biology/src/Game.h
        biology/src/Player.cpp
        biology/src/Player.h
        biology/src/Board.cpp
        biology/src/Board.h
        biology/src/Judge.cpp
        biology/src/Judge.h
        biology/src/Chess.cpp
        biology/src/Chess.h
        biology/src/Human.cpp
        biology/src/Human.h
        biology/src/AI.cpp
        biology/src/AI.h
        biology/src/Display.cpp
        biology/src/Display.h
        biology/src/AlpheBeta.cpp
        biology/src/AlpheBeta.h
        biology/src/Evaluate.cpp
        biology/src/Evaluate.h)
