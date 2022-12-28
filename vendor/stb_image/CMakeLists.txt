add_library(
        stb
        stb_impl.cpp
        stb_image.h
        stb_image.cpp
)

target_include_directories(stb PRIVATE "../")

set_target_properties(stb PROPERTIES POSITION_INDEPENDENT_CODE TRUE)