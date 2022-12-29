#include "error.h"
#include <iostream>

void GLClearError()
{
	while (glGetError() != GL_NO_ERROR)
		;
}

bool GLLogError(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{

		std::cout << "[OpenGL Error] (" << error << ")\nIn File " << file << "\nIn line" << line << "\nIn Function"
		          << function;
		return false;
	}
	return true;
}