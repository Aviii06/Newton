#include "Mesh.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

Mesh::Mesh(Vector<Vertex> &verts, Vector<unsigned int> &inds, VertexBufferLayout layout, glm::mat4 modelMatrix) {
    Mesh::m_Vertices = verts;
    Mesh::m_Indices = inds;
    Mesh::m_Layout = layout;
    Mesh::m_ModelMatrix = modelMatrix;
}

void Mesh::Update(const Vector<Vertex> &verts) {
    for (int i = 0; i < verts.size(); i++) {
        m_Vertices[i].isLit = verts[i].isLit;
    }
}

Vector<Vertex> Mesh::getVertices() {
    return Mesh::m_Vertices;
}

Vector<unsigned int> Mesh::getIndices() {
    return Mesh::m_Indices;
}

glm::mat4 Mesh::getModelMatrix() {
    return Mesh::m_ModelMatrix;
}

void Mesh::Draw(Shader &shader, Renderer &renderer, glm::mat4 &modelMatrix) {
    VertexBuffer vbo(m_Vertices);
    IndexBuffer ebo(m_Indices);
    vbo.Bind();
    ebo.Bind();

    vao.AddBuffer(vbo, m_Layout);
    vao.Bind();

    shader.Bind();
    m_ModelMatrix = modelMatrix;
    shader.SetUniformMat4f("u_Model", m_ModelMatrix);
    renderer.Draw(vao, ebo, shader);
}
