cmake_minimum_required(VERSION 3.28)
project(prog_rgz_c C)

set(CMAKE_C_STANDARD 11)

add_executable(prog_rgz_c main.c
        TV.h
        TVList.h
        FileManager.h
        Menu.h
)
