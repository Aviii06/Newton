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
	VertexBufferLayout m_Layout;

    VertexArray vao;

	// Initializes the mesh
	Mesh(std::vector <Vertex>& vertices, std::vector <unsigned int>& indices, VertexBufferLayout layout);

	void Update(const Vector<Vertex>& vertices);
	Vector<Vertex> getVertices();
	Vector<unsigned int> getIndices();
	// Draws the mesh
	void Draw(Shader& shader, Renderer& renderer);
};
