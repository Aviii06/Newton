cmake_minimum_required(VERSION 3.16)
cmake_policy(SET CMP0091 NEW)

project(Newton)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_VERBOSE_MAKEFILE ON CACHE BOOL "ON")


add_subdirectory(vendor)

add_executable(${PROJECT_NAME} src/main.cpp src/renderer/Camera.cpp src/renderer/Camera.h src/renderer/PointLight.cpp src/renderer/PointLight.h src/renderer/shapes/Quad3d.cpp src/renderer/shapes/Quad3d.h src/renderer/shapes/Sphere.cpp src/renderer/shapes/Sphere.h)
add_subdirectory(src)






