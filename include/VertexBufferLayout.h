#pragma once

#include <cassert>
#include <vector>
#include <glad/glad.h>

#include "Utils.h"

struct VertexBufferAttribute {
        GLenum Type;
        GLboolean Normalized;
        unsigned int ElementAmount;
};

class VertexBufferLayout {
public:
        template<typename T>
        void Push(bool normalized, unsigned int ElementAmount);

        inline const std::vector<VertexBufferAttribute>& GetAttributes() const { return m_Attributes; }
        inline const unsigned int GetElementSize() const { return m_ElementSize; }

private:
        std::vector<VertexBufferAttribute> m_Attributes {};
        unsigned int m_ElementSize {};
};

template<typename T>
void VertexBufferLayout::Push(bool normalized, unsigned int ElementAmount) {
        assert(false && "Undefined Type for VertexBufferLayout");
}

template<>
inline void VertexBufferLayout::Push<float>(bool normalized, unsigned int ElementAmount) {
        VertexBufferAttribute attributePointer { 
                GL_FLOAT, 
                normalized ? GL_TRUE : GL_FALSE, 
                ElementAmount 
        };

        m_ElementSize += getSizeOfType(GL_FLOAT) * ElementAmount;
        m_Attributes.push_back(attributePointer);
}

