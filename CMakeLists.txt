cmake_minimum_required(VERSION 3.17)
project(CW1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/third_party/parlaylib/include)

add_executable(benchmark src/main.cpp)
add_executable(test tests/test.cpp)