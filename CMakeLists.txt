cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(ncfw)

add_library(
    ncfw STATIC
    ncfw/src/Logger.cpp
)

target_include_directories(
    ncfw
    PUBLIC ncfw/include/
)

add_executable(
    ncfw_sandbox
    ncfw_sandbox/main.cpp
)

target_link_libraries(
    ncfw_sandbox
    PUBLIC ncfw
)

