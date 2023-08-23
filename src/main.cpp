#include "Vivid.h"
#include "UI/UI.h"

InputHandler* InputHandler::s_Instance;
Vivid::Camera* Vivid::Camera::s_Instance;

class ExampleInterface : public RenderingInterface
{
private:
	Vec3 lightColor = Vec3(1.0f, 0.5f, 1.0f);
	Vec3 lightPos = Vec3(0.0f, 0.0f, -100.0f);
	Vec2* m_PrevMousePosition = new Vec2(0.0f, 0.0f);

public:
	void Setup() override
	{
		// Can write custom opengl confs here
		OPENGL_CONFS

		Vivid::Renderer2D::Init();

		// Light Info
		Vivid::Quad3d cube(10.0f, lightColor);
		Vivid::Mesh lightMesh(cube);
		Vivid::PointLight light(lightPos, lightColor, &lightMesh);
		Ref<Vivid::Shader> lightShader = MakeRef<Vivid::Shader>("./../assets/shaders/basic.vertexShader.glsl",
		    "./../assets/shaders/basic.pixelShader.glsl");
		light.Draw(lightShader);

		// Creating a shader
		Ref<Vivid::Shader> shader = MakeRef<Vivid::Shader>("./../assets/shaders/phong.vertexShader.glsl",
		    "./../assets/shaders/phong.pixelShader.glsl");

		// Drawing other meshes
		Vivid::Mesh mesh1("./../assets/obj/suzanne.obj");
		mesh1.BindShader(shader);

		glm::vec3 translationModel1(0, 50, -200);

		mesh1.Update(glm::translate(glm::mat4(1.0f), translationModel1));
		shader->SetUniform3f("lightColor", lightColor);
		shader->SetUniform3f("lightPos", lightPos);
		shader->SetUniform1f("intensity", 2.0f);

		shader->Bind();
		mesh1.Update(glm::translate(glm::mat4(1.0f), translationModel1));
		mesh1.Draw();

		light.UpdateLightPosition(lightPos);
		light.Draw(lightShader);
	}

	void Draw() override
	{
		Ref<Vivid::Shader> shader = MakeRef<Vivid::Shader>("./../assets/shaders/phong.vertexShader.glsl",
		    "./../assets/shaders/phong.pixelShader.glsl");

		// Drawing other meshes
		Vivid::Mesh mesh1("./../assets/obj/suzanne.obj");
		mesh1.BindShader(shader);

		glm::vec3 translationModel1(0, 50, -200);

		shader->SetUniform3f("lightColor", lightColor);
		shader->SetUniform3f("lightPos", lightPos);
		shader->SetUniform1f("intensity", 2.0f);

		shader->Bind();
		mesh1.Update(glm::translate(glm::mat4(1.0f), translationModel1));
		mesh1.Draw();
	}

	void ImGuiRender() override
	{
		ImGui::Begin("Debug");
		//	ImGui::SliderFloat3("Translation Model 1", &translationModel1.x, -500.0f, 500.0f);
		//	// ImGui::SliderFloat3("Translation Model 2", &translationModel2.x, -300.0f, 300.0f);
		//	ImGui::SliderFloat3("Light Position", &lightPos.x, -500.0f, 500.0f);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
		    1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

		ImGui::End();

		NewtonUI::Draw();
	}

	void Input() override
	{
		if (InputHandler::GetInstance()->IsKeyPressed(GLFW_KEY_W))
		{
			InputHandler::GetInstance()->GetCamera()->MoveForward();
		}
		if (InputHandler::GetInstance()->IsKeyPressed(GLFW_KEY_S))
		{
			InputHandler::GetInstance()->GetCamera()->MoveBackward();
		}
		if (InputHandler::GetInstance()->IsKeyPressed(GLFW_KEY_A))
		{
			InputHandler::GetInstance()->GetCamera()->MoveLeft();
		}
		if (InputHandler::GetInstance()->IsKeyPressed(GLFW_KEY_D))
		{
			InputHandler::GetInstance()->GetCamera()->MoveRight();
		}

		Vec2 mousePosition = InputHandler::GetInstance()->GetMousePosition();
		if (InputHandler::GetInstance()->IsMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT))
		{
			InputHandler::GetInstance()->GetCamera()->ProcessMouseMovement(mousePosition.x - m_PrevMousePosition->x,
			    mousePosition.y - m_PrevMousePosition->y);
			m_PrevMousePosition->x = mousePosition.x;
			m_PrevMousePosition->y = mousePosition.y;
		}
		else
		{
			m_PrevMousePosition->x = mousePosition.x;
			m_PrevMousePosition->y = mousePosition.y;
		}
	}
};

Application* Vivid::CreateApplication()
{
	Application* app = Application::GetInstance(1920, 1080, "Newton");
	app->SetRenderingInterface(new ExampleInterface);
	return app;
}

int main()
{
	return Vivid::main(0, nullptr);
}