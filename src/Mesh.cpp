#include "Mesh.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

Mesh::Mesh(Vector<Vertex>& verts, Vector<unsigned int>& inds, Vector <Texture>& textures, VertexBufferLayout layout)
{   
    Mesh::m_Vertices = verts;
    Mesh::m_Indices = inds;
	Mesh::m_Textures = textures;
    Mesh::m_Layout = layout;
}

void Mesh::Draw()
{
    VertexBuffer vbo(m_Vertices);
    IndexBuffer ebo(m_Indices);
    vbo.Bind();
    ebo.Bind();

    vao.AddBuffer(vbo, m_Layout);
    vao.Bind();

    for(auto&& x: m_Textures)
    {
        x.Bind();
    }
    glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, nullptr);
}

