#pragma once
#include "common/Types.h"
#include "utils/Error.h"
#include "renderer/Renderer.h"
#include "renderer/Mesh.h"
#include "renderer/Camera.h"

namespace NewtonRenderer
{
	struct Storage
	{
		Mesh* mesh;
		Ref<Shader> shader;
	};
	class Renderer2D
	{
	private:
		static Storage s_Storage;
		Renderer2D() = default;
		~Renderer2D() = default;

	public:
		static void Init();
		static void Shutdown();

		static void BeginScene();
		static void EndScene();

		static void DrawQuad();
	};
}