cmake_minimum_required(VERSION 3.10)
project(LibraryManagementSystem)
# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ========== 主程序 ==========
include_directories(src) # 告诉 CMake 去哪里找头文件

find_package(SQLite3 REQUIRED) # 查找 SQLite3 库

add_executable(lms
    src/library.cpp
    src/main.cpp
) # 添加可执行文件

target_link_libraries(lms SQLite::SQLite3) # 链接 SQLite3

# ========== 测试程序 ==========
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(test_library
    tests/test_library.cpp
    src/library.cpp
)
target_link_libraries(test_library ${GTEST_LIBRARIES} sqlite3 pthread)
