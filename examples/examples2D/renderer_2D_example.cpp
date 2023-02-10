#include "Vivid.h"

class ExampleInterface : public RenderingInterface
{
public:
	void Setup() override
	{
		OPENGL_2D_CONFS

		Vivid::Renderer2D::Init();
	}

	void Draw() override
	{
		Vivid::Renderer2D::BeginScene();

		// Draw using API
		Vivid::Renderer2D::DrawCircle(Vec2(0, 0), 150, Vec3(0.0f, 1.0f, 0.0f));

		Vivid::Renderer2D::DrawLine(Vec2(-150, 0), Vec2(150, 0), 2,
		    Vec3(1.0f, 0.5f, 0.0f));

		Vivid::Renderer2D::DrawQuad(-200, -200, 100, 100, Vec3(1.0f, 1.0f, 0.0f));

		Vivid::Renderer2D::EndScene();
	}

	void ImGuiRender() override
	{
		// IMGUI
		ImGui_ImplGlfw_NewFrame();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Debug");
		//	ImGui::SliderFloat3("Translation Model 1", &translationModel1.x, -500.0f, 500.0f);
		//	// ImGui::SliderFloat3("Translation Model 2", &translationModel2.x, -300.0f, 300.0f);
		//	ImGui::SliderFloat3("Light Position", &lightPos.x, -500.0f, 500.0f);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
		    1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

		ImGui::End();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
};

Application* Vivid::CreateApplication()
{
	Application* app = Application::GetInstance(1920, 1080, "Rendering2D");
	app->SetRenderingInterface(new ExampleInterface);
	return app;
}

int main()
{
	return Vivid::main(0, nullptr);
}