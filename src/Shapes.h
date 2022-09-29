#pragma once
#include <stddef.h>

namespace shape{
    class quad3d;
}


class shape::quad3d{
private:
    float m_Size;
    float m_Pos[8*8];
    unsigned int m_Ind[12*3];
public:
    quad3d(int size);
    float* getPositions();
    unsigned int* getIndices();
    size_t getPositionsSize();
    size_t getIndicesSize();
};
    
