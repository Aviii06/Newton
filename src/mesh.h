#pragma once

#include "../utils/error.h"
#include "../common/types.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "Renderer.h"
#include "VertexBufferLayout.h"

class Mesh
{
public:
	Vector <Vertex> m_Vertices;
	Vector <GLuint> m_Indices;
	Vector <Texture> m_Textures;

    VertexArray vao;

	// Initializes the mesh
	Mesh(std::vector <Vertex>& vertices, std::vector <unsigned int>& indices, std::vector <Texture>& textures, VertexBufferLayout layout);

	// Draws the mesh
	void Draw();
};
