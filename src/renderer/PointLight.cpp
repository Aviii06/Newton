#include "PointLight.h"

namespace NewtonRenderer
{
	PointLight::PointLight(Vec3 position, Vec3 color, Mesh* lightMesh)
	{
		m_Position = position;
		m_Color = color;
		m_LightMesh = lightMesh;
	}

	PointLight::PointLight(Vec3 position, Vec3 color, Shape& shape)
	{
		m_Position = position;
		m_Color = color;
		m_LightMesh = new Mesh(shape);
	}

	void PointLight::UpdateLightPosition(Vec3 pos)
	{
		m_Position = pos;
		glm::vec3 tempPos = glm::vec3(m_Position.x, m_Position.y, m_Position.z);
		m_LightMesh->Update(glm::translate(glm::mat4(1.0f), tempPos));
	}

	void PointLight::Draw(Ref<Shader> shader)
	{
		shader->Bind();
		shader->SetUniform3f("lightColor", m_Color);
		shader->SetUniform3f("lightPos", m_Position);
		m_LightMesh->BindShader(std::move(shader));
		m_LightMesh->Draw();
	}
}
