#pragma once

#include "../utils/error.h"
#include "../common/types.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "Renderer.h"

class Mesh
{
private:
	VertexArray m_VertexArray;
	IndexBuffer m_IndexBuffer;
public:
	// Initializes the mesh
	Mesh(Vector<float>& pos, Vector<float>& normals, Vector<unsigned int>& ind, std::vector <Texture>& textures, VertexBufferLayout layout);

	// Draws the mesh
	void Draw(Shader& shader);
};
