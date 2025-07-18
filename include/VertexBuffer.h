#pragma once

#include <cstddef>  

class VertexBuffer {
public:
    void Init();
    void Bind();
    void Unbind();
    void SetData(float vertices[], std::size_t size);
    ~VertexBuffer();

private:
    unsigned int m_BufferId;
    bool m_Bound; 
    bool m_Initialised;
};
