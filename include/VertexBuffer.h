#pragma once

#include <glad/glad.h>

class VertexBuffer {
public:
    void Init();
    void Bind();
    void Unbind();
    void SetData();

private:
    unsigned int m_BufferId;
    bool m_Bound; 
    bool m_Initialised;
}
