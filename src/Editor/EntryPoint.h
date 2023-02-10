#pragma once

#include "Editor/Application.h"

Application* Vivid::CreateApplication();

namespace Vivid
{
	int main(int argc, char** argv)
	{
		Application* app = CreateApplication();
		app->Run();
		app->Terminate();
		return 0;
	}
}