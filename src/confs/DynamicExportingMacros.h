#pragma once

#if defined _WIN32
#define VIVAPI __declspec(dllexport)
#elif __APPLE__
#define VIVAPI __attribute__((visibility("default")))
#elif __linux__
#define VIVAPI
#endif