#include "PointLight.h"

PointLight::PointLight(glm::vec3 position, glm::vec3 color, Mesh* lightMesh)
{
	m_Position = position;
	m_Color = color;
	m_LightMesh = lightMesh;
}

PointLight::PointLight(glm::vec3 position, glm::vec3 color, Shape& shape)
{
	m_Position = position;
	m_Color = color;
	m_LightMesh = new Mesh(shape);
}

void PointLight::UpdateLightPosition(glm::vec3 pos)
{
	m_Position = pos;
	m_LightMesh->Update(glm::translate(glm::mat4(1.0f), m_Position));
}

void PointLight::Draw(Shader& shader, Renderer& renderer, Camera camera)
{
	shader.Bind();
	shader.SetUniform3f("lightColor", m_Color);
	shader.SetUniform3f("lightPos", m_Position);
	m_LightMesh->Draw(shader, renderer, camera);
}
