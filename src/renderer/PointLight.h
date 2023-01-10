#pragma once

#include "Mesh.h"
#include "shapes/Shape.h"

class PointLight
{
private:
	glm::vec3 m_Position;
	glm::vec3 m_Color;
	Mesh* m_LightMesh;

public:
	PointLight(glm::vec3 position, glm::vec3 color, Mesh* lightMesh);
	PointLight(glm::vec3 position, glm::vec3 color, Shape& shape);

	void UpdateLightPosition(glm::vec3 pos);

	void Draw(Shader& shader, Renderer& renderer, Camera camera);
};