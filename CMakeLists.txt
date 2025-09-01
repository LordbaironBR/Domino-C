cmake_minimum_required(VERSION 3.31)
project(Domino C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Domino
        Controller.c
        Main.c
        Model.c
        View.c)
