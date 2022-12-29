#pragma once

#include <GL/glew.h>
#if defined(__GNUC__) || defined(__GNUG__) || defined(__clang__)
#define ASSERT(x) \
	if (!(x))     \
	__builtin_trap()
#elif defined(_MSC_VER)
#define ASSERT(x) \
	if (!(x))     \
	__debugbreak()
#endif


#define GLCall(x)   \
	GLClearError(); \
	x;              \
	ASSERT(GLLogError(#x, __FILE__, __LINE__))

void GLClearError();

bool GLLogError(const char* function, const char* file, int line);
