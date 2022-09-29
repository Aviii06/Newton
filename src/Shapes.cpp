#include "Shapes.h"

namespace shape{
    quad3d::quad3d(int size)
    {
        m_Size = (float)size;
        float pos[] = {
            -m_Size, m_Size, -m_Size,         0.0, 0.0,           0.1, 0.3, 0.8,
            m_Size, m_Size, -m_Size,          1.0, 0.0,           0.8, 0.44, 0.32,
            -m_Size, -m_Size, -m_Size,        1.0, 1.0,           0.12, 0.5, 0.21,
            m_Size, -m_Size, -m_Size,         0.0, 1.0,           0.144, 0.33, 0.48, 
            -m_Size, m_Size, m_Size,          0.0, 0.0,           0.52, 0.23, 0.21,
            m_Size, m_Size, m_Size,           1.0, 0.0,           0.25, 0.43, 0.71,   
            -m_Size, -m_Size, m_Size,         1.0, 1.0,           0.56, 0.35, 0.19,
            m_Size, -m_Size, m_Size,          0.0, 1.0,           0.34, 0.31, 0.43,
        }; 

        unsigned int ind[] = {
            0, 1, 2, // Side 0
            2, 1, 3,
            4, 0, 6, // Side 1
            6, 0, 2,
            7, 5, 6, // Side 2
            6, 5, 4,
            3, 1, 7, // Side 3 
            7, 1, 5,
            4, 5, 0, // Side 4 
            0, 5, 1,
            3, 7, 2, // Side 5 
            2, 7, 6
        };
        
        int i = 0;
        for(auto x: pos)
        {
            m_Pos[i] = x;
            i++;
        }
        
        i = 0;
        for(auto x: ind)
        {
            m_Ind[i] = x;
            i++;
        }

    }

    float* quad3d::getPositions() { return m_Pos; }   
    unsigned int* quad3d::getIndices() { return m_Ind; }   

    size_t quad3d::getPositionsSize() { return sizeof(m_Pos); }
    size_t quad3d::getIndicesSize() { return sizeof(m_Ind)/sizeof(m_Ind[0]); }
}

