cmake_minimum_required(VERSION 3.6)
project(BMP2TXT)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
    bmp2txt.c image.c image.h)

add_executable(bmp2txt ${SOURCE_FILES})