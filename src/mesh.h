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
	glm::mat4 m_ModelMatrix;

    VertexArray vao;

	// Initializes the mesh
	Mesh(Vector<Vertex>& verts, Vector<unsigned int>& inds, VertexBufferLayout layout, glm::mat4 modelMatrix);

	void Update(const Vector<Vertex>& vertices);
	Vector<Vertex> getVertices();
	Vector<unsigned int> getIndices();
	glm::mat4 getModelMatrix();
	// Draws the mesh
	void Draw(Shader& shader, Renderer& renderer, glm::mat4& modelMatrix);
};
