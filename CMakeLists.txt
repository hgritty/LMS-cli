cmake_minimum_required(VERSION 3.10)
project(LibraryManagementSystem)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 告诉 CMake 去哪里找头文件
include_directories(src)

# 添加可执行文件
add_executable(lms
    src/library.cpp
    src/main.cpp
)
