cmake_minimum_required(VERSION 3.16)
cmake_policy(SET CMP0091 NEW)

project(Newton)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_VERBOSE_MAKEFILE ON CACHE BOOL "ON")


add_subdirectory(vendor)

add_subdirectory(src)






