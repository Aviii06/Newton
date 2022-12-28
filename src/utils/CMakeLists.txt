set(UTILS
        ${CMAKE_CURRENT_SOURCE_DIR}/error.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/error.h
        ${CMAKE_CURRENT_SOURCE_DIR}/timer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/timer.h
        CACHE INTERNAL "")

add_library(utils SHARED ${UTILS})