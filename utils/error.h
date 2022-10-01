#pragma once

#include<GL/glew.h>

#define ASSERT(x) if (!(x)) __builtin_trap()

#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogError(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogError(const char* function, const char* file, int line);
