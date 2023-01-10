#pragma once

#include "IndexBuffer.h"
#include "Renderer.h"
#include "Texture.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Camera.h"
#include "Shapes/Shape.h"

#include "../common/types.h"
#include "../utils/error.h"

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>

class Mesh
{
private:
	Vector<Vertex> m_Vertices;
	Vector<GLuint> m_Indices;
	VertexBufferLayout m_Layout;
	VertexArray m_Vao;
	IndexBuffer* m_Ebo;

	glm::mat4 m_ModelMatrix;

public:
	// Initializes the mesh
	Mesh(Vector<Vertex>& verts, Vector<unsigned int>& inds, VertexBufferLayout layout, glm::mat4 modelMatrix);
	explicit Mesh(Shape& shape);
	explicit Mesh(const std::string& file_name);

	void Update(const glm::mat4& modelMatrix);

	Vector<Vertex> getVertices() { return m_Vertices; }

	Vector<unsigned int> getIndices() { return m_Indices; };

	glm::mat4 getModelMatrix() { return m_ModelMatrix; };

	// Draws the mesh
	void Draw(Shader& shader, Renderer& renderer, Camera& camera);
};
