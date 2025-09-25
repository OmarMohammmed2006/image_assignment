cmake_minimum_required(VERSION 3.30)
project(Code)

set(CMAKE_CXX_STANDARD 20)

add_executable(Code main.cpp
        Image_Class.h
        stb_image.h
        stb_image_write.h
)
