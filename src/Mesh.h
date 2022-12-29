#pragma once

#include "IndexBuffer.h"
#include "Renderer.h"
#include "Texture.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "common/types.h"
#include "utils/error.h"

class Mesh {
public:
    Vector<Vertex> m_Vertices;
    Vector<GLuint> m_Indices;
    Vector<Texture> m_Textures;
    VertexBufferLayout m_Layout;
    glm::mat4 m_ModelMatrix;

    VertexArray vao;

    // Initializes the mesh
    Mesh(Vector<Vertex> &verts, Vector<unsigned int> &inds, VertexBufferLayout layout, glm::mat4 modelMatrix);

    void Update(const Vector<Vertex> &vertices);

    Vector<Vertex> getVertices();

    Vector<unsigned int> getIndices();

    glm::mat4 getModelMatrix();

    // Draws the mesh
    void Draw(Shader &shader, Renderer &renderer, glm::mat4 &modelMatrix);
};
