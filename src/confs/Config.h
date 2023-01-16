#pragma once

#define OPENGL_CONFS                                            \
	glEnable(GL_DEPTH_TEST);                                    \
	if (glewInit() != GLEW_OK)                                  \
	{                                                           \
		std::cout << "GLEW failed to initialize!" << std::endl; \
	}                                                           \
	GLCall(glEnable(GL_BLEND));                                 \
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

#if defined(IMGUI_IMPL_OPENGL_ES2)
#define IMGUI_CONFS                                \
	const char* glsl_version = "#version 100";     \
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2); \
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0); \
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);

#elif defined(__APPLE__)
#define IMGUI_CONFS                                                \
	const char* glsl_version = "#version 150";                     \
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);                 \
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);                 \
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); \
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

#else
#define IMGUI_CONFS                                \
	const char* glsl_version = "#version 130";     \
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); \
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

#endif
