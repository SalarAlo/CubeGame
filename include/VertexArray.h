#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray {
public:
        void Init();
        void Bind();
        void Unbind();
        void ConnectLayoutToBuffer(VertexBuffer& buffer, const VertexBufferLayout& layout);

        ~VertexArray();

private:
        unsigned int m_ArrayId;       
        bool m_Bound;
        bool m_Initialised;
};
