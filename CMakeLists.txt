cmake_minimum_required(VERSION 3.10)

project(UnixProgramming)

set(BIN_DIR ${CMAKE_BINARY_DIR}/bin)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    # 在调试构建中添加调试信息并关闭优化
    SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
endif()



# 将该变量传递给子目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})

add_subdirectory(IO)
add_subdirectory(FileSystem)
add_subdirectory(String_test)
add_subdirectory(Thread)
add_subdirectory(Process)
