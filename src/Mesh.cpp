#include "Mesh.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

Mesh::Mesh(Vector<Vertex>& verts, Vector<unsigned int>& inds, VertexBufferLayout layout)
{   
    Mesh::m_Vertices = verts;
    Mesh::m_Indices = inds;
    Mesh::m_Layout = layout;
}

void Mesh::Draw(Shader& shader, Renderer& renderer)
{
    VertexBuffer vbo(m_Vertices);
    IndexBuffer ebo(m_Indices);
    vbo.Bind();
    ebo.Bind();

    vao.AddBuffer(vbo, m_Layout);
    vao.Bind();

    renderer.Draw(vao, ebo, shader);
}

