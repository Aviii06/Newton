#pragma once

#include "IndexBuffer.h"
#include "Renderer.h"
#include "Texture.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Camera.h"
#include "shapes/Shape.h"

#include "../common/types.h"
#include "../utils/error.h"

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>

namespace NewtonRenderer
{
	class Mesh
	{
	private:
		Vector<Vertex> m_Vertices;
		Vector<GLuint> m_Indices;
		VertexBufferLayout m_Layout;
		VertexArray m_Vao;
		IndexBuffer* m_Ebo;
		Shader* m_Shader;

		glm::mat4 m_ModelMatrix;

		void loadOBJ(const std::string& file_name);

	public:
		// Initializes the mesh
		Mesh(Vector<Vertex>& verts, Vector<unsigned int>& inds, VertexBufferLayout layout, glm::mat4 modelMatrix);
		explicit Mesh(Shape& shape);
		explicit Mesh(const std::string& file_name);
		explicit Mesh(const std::string& file_name, Shader* shader);

		void Update(const glm::mat4& modelMatrix);

		void BindShader(Shader* shader);

		Vector<Vertex> getVertices() { return m_Vertices; }

		Vector<unsigned int> getIndices() { return m_Indices; };

		glm::mat4 getModelMatrix() { return m_ModelMatrix; };

		// Draws the mesh
		void Draw();
	};
}
