cmake_minimum_required(VERSION 3.11)
project(miner C)

set(CMAKE_C_STANDARD 99)

add_executable(miner main.c mempool.c mempool.h siggen.c siggen.h)