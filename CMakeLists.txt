cmake_minimum_required(VERSION 3.16)
cmake_policy(SET CMP0091 NEW)

project(Newton)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fdiagnostics-color=always")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -Wall")
set(CMAKE_C_COMPILER "/usr/local/bin/gcc")
set(CMAKE_CXX_COMPILER "/usr/local/bin/g++")

# Add source files
file(GLOB_RECURSE SOURCE_FILES src/**.cpp)
	
# Add header files
file(GLOB_RECURSE HEADER_FILES src/**.h)

add_executable(${PROJECT_NAME} main.cpp ${HEADER_FILES} ${SOURCE_FILES})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/dependancies/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/dependancies/library/libGLEW.2.2.0.dylib ${CMAKE_CURRENT_SOURCE_DIR}/dependancies/library/libglfw.3.3.dylib)

macro(ADD_FRAMEWORK fwname appname)
find_library(FRAMEWORK_${fwname}
    NAMES ${fwname}
    PATHS ${CMAKE_OSX_SYSROOT}/System/Library
    PATH_SUFFIXES Frameworks
    NO_DEFAULT_PATH)
if( ${FRAMEWORK_${fwname}} STREQUAL FRAMEWORK_${fwname}-NOTFOUND)
    MESSAGE(ERROR ": Framework ${fwname} not found")
else()
    TARGET_LINK_LIBRARIES(${appname} PRIVATE ${FRAMEWORK_${fwname}})
    MESSAGE(STATUS "Framework ${fwname} found at ${FRAMEWORK_${fwname}}")
endif()
endmacro(ADD_FRAMEWORK)

add_framework(OpenGl ${PROJECT_NAME})
add_framework(Cocoa ${PROJECT_NAME})
add_framework(IOKit ${PROJECT_NAME})
add_framework(CoreVideo ${PROJECT_NAME})
add_framework(CoreFoundation ${PROJECT_NAME})
add_framework(GLUT ${PROJECT_NAME})
