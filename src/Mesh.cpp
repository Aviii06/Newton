#include "Mesh.h"
#include "VertexBufferLayout.h"

Mesh::Mesh(Vector<float>& pos, Vector<float>& normals, Vector<unsigned int>& ind, std::vector <Texture>& textures, VertexBufferLayout layout)
{   
    const Vector<VertexBufferElement> elements = layout.GetElements();
    
    Vector<unsigned int> counts;
    Vector<unsigned int> ends;
    unsigned int sum = 0;

    for (unsigned int i = 0; i < elements.size() ; i++)
    {
        counts.push_back(elements[i].count);
        ends.push_back(0);
        const VertexBufferElement element = elements[i];
        sum += element.count;
    }

    float positions[(pos.size() * sum)/ counts[0]];
    for(int i=0; i<(pos.size() * sum)/ counts[0]; i += 8)
    {
        // positions
        int s = 0;
        for(int j = 0; j < counts[0]; j++ )
        {
            positions[i + j] = pos[ends[0] + j]; 
            ends[0] += counts[0];
        }

        // TexCoords
        s += counts[0];
        for(int j = 0; j < counts[1]; j++)
        {
            positions[i + s + j] = 1.0;
        }


        // Colors
        s += counts[1];
        for(int j=0; j < counts[2]; j++)
        {
            positions[i + s + j] = 1.0;
        }

        // normals
        s += counts[2];
        for(int j=0; j < counts[3]; j++)
        {
            positions[i + s + j] = normals[ends[3] + j];
            ends[3] += counts[3];
        }
    }    

    unsigned int j = 0;

    unsigned int indices[ind.size()];
    for(auto x : ind)
    {
        indices[j] = x;
        j++;
    }

    size_t indSize = sizeof(indices) / sizeof(indices[0]);
    size_t posSize = sizeof(positions);  

    VertexBuffer vb(positions, posSize);
    
    m_VertexArray.AddBuffer(vb, layout);

    m_IndexBuffer = IndexBuffer(indices, indSize);
}

void Mesh::Draw(Shader &shader)
{
    Renderer renderer; 
    renderer.Draw(m_VertexArray, m_IndexBuffer, shader);
}

