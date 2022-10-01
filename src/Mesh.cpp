#include "Mesh.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

Mesh::Mesh(Vector<Vertex>& verts, Vector<unsigned int>& inds, Vector <Texture>& textures, VertexBufferLayout layout)
{   
    Mesh::m_Vertices = verts;
    Mesh::m_Indices = inds;
	Mesh::m_Textures = textures;

    vao.Bind();

    VertexBuffer vbo(m_Vertices);
    IndexBuffer ebo(m_Indices);
    
    vao.AddBuffer(vbo, layout);
    
    vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();
}

void Mesh::Draw()
{
    vao.Bind();
    for(auto x: m_Textures)
    {
        x.Bind();
    }
    glDrawElements(GL_TRIANGLES, 0, GL_UNSIGNED_INT, nullptr);
}

