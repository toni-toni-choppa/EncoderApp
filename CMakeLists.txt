cmake_minimum_required(VERSION 3.10)
project(EncoderApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(EncoderApp src/main.cpp)

add_subdirectory(libs/libutils)
include_directories(libs/libutils/include)

target_link_libraries(EncoderApp PRIVATE utils)