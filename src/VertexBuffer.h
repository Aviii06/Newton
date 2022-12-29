#ifndef vertexbuffer
#define vertexbuffer

#include<glm/glm.hpp>
#include "common/types.h"

// Structure to standardize the vertices used in the meshes
struct Vertex {
    glm::vec3 position;
    glm::vec2 texcoord;
    glm::vec3 color;
    glm::vec3 normal;
    float isLit;
};

class VertexBuffer {
private:
    unsigned int m_RendererID;
public:
    VertexBuffer(std::vector<Vertex> &vertices);

    ~VertexBuffer();

    void Bind() const;

    void Unbind() const;
};

#endif
