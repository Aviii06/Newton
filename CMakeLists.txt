project(Projet_AIN CXX)
cmake_minimum_required(VERSION 2.8)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_C_COMPILER usr/local/bin/gcc)
set(CMAKE_CPP_COMPILER usr/local/bin/g++)

add_executable(Newton "src/main.cpp")

target_include_directories(Newton PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/dependancies/include)
target_link_libraries(Newton PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/dependancies/library/libGLEW.2.2.0.dylib ${CMAKE_CURRENT_SOURCE_DIR}/dependancies/library/libglfw.3.3.dylib)

target_link_libraries(Newton
    "-framework OpenGl"
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
    "-framework CoreFoundation"
    "-framework GLUT"
    )
