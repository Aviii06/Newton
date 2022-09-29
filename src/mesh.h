#pragma once

#include "../utils/error.h"
#include "../common/types.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Texture.h"

class Mesh
{
public:
	std::vector <VertexArray> m_Vertices;
	std::vector <GLuint> m_Indices;
	std::vector <Texture> m_Textures;
	// Store VAO in public so it can be used in the Draw function
	VertexBuffer VertexBuffer;

	// Initializes the mesh
	Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures);

	// Draws the mesh
	void Draw(Shader& shader, Camera& camera);
};
