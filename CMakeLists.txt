cmake_minimum_required(VERSION 3.26)
project(CompressionProject C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(CompressionProject
        compression.c
        dataPreperation.c
        dataPreperation.h
        huffman.c
        huffman.h
)
