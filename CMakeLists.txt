cmake_minimum_required(VERSION 3.10)

project(UnixProgramming)


set(BIN_DIR ${CMAKE_BINARY_DIR}/bin)

# 将该变量传递给子目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})

add_subdirectory(IO)