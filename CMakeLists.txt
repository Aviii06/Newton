cmake_minimum_required(VERSION 3.16)
cmake_policy(SET CMP0091 NEW)

project(Newton)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fdiagnostics-color=always")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -Wall")

# Add source files
file(GLOB_RECURSE SOURCE_FILES src/**.cpp utils/**.cpp dependancies/include/imgui/**.cpp)
	
# Add header files
file(GLOB_RECURSE HEADER_FILES src/**.h common/**.h utils/**.h dependancies/include/imgui/**.h dependancies/include/**.hpp)

add_executable(${PROJECT_NAME} main.cpp ${HEADER_FILES} ${SOURCE_FILES})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/dependancies/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/src/stb_image ${CMAKE_CURRENT_SOURCE_DIR}/common ${CMAKE_CURRENT_SOURCE_DIR}/utils)

target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/dependancies/library/glew32.lib ${CMAKE_CURRENT_SOURCE_DIR}/dependancies/library/glfw3.lib)
