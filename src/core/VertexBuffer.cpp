#include "VertexBuffer.h"
#include <cassert>

void VertexBuffer::Bind() {
    assert(m_Initialised && m_Bound && "VBO hasnt been initialised or is already bound")
    glBindBuffer(GL_ARRAY_BUFFER, m_BufferId);
    
}

void VertexBuffer::Init() {
    assert(!m_Initialised && "VBO already initialised")
    glGenBuffers(1, &m_BufferId);

    m_Initialised = true;
}
