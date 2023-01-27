#include "UI.h"
#include "imgui/imgui/backends/imgui_impl_glfw.h"
#include "imgui/imgui/backends/imgui_impl_opengl3.h"
#include "imgui/imgui/imgui.h"

#include "confs/Config.h"
#include "Editor/Application.h"

void UI::Update()
{

	ImGui_ImplGlfw_NewFrame();
	ImGui_ImplOpenGL3_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Debug");
	//	ImGui::SliderFloat3("Translation Model 1", &translationModel1.x, -500.0f, 500.0f);
	//	// ImGui::SliderFloat3("Translation Model 2", &translationModel2.x, -300.0f, 300.0f);
	//	ImGui::SliderFloat3("Light Position", &lightPos.x, -500.0f, 500.0f);
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
	    1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

//	m_OnUpdate();

	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

UI* UI::Init()
{
	IMGUI_CONFS

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(Application::GetInstance()->GetWindow().GetGLFWWindow(), true);
	ImGui_ImplOpenGL3_Init(glsl_version);
	ImGui::StyleColorsDark();

//	m_OnUpdate = onUpdate;
	return this;
}
