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

void Mesh::Update(const Vector<Vertex>& verts)
{
    for (int i = 0 ; i < verts.size() ; i++)
    {
        m_Vertices[i].isLit = verts[i].isLit;
    }
}

Vector<Vertex> Mesh::getVertices()
{
    return Mesh::m_Vertices;
}

Vector<unsigned int> Mesh::getIndices()
{
    return Mesh::m_Indices;
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

