#include "VertexArray.h"
#include "Utils.h"
#include "VertexBufferLayout.h"

#include <cassert>

#include <cstdint>
#include <glad/glad.h>

void VertexArray::Init() {
        assert(!m_Initialised && "Vertex Array already Initialised");
        glGenVertexArrays(1, &m_ArrayId);
        m_Initialised = true;
}

void VertexArray::Bind() {
        assert(m_Initialised && !m_Bound && "VertexArray is already bound or not Initialised");
        glBindVertexArray(m_ArrayId);
        m_Bound = true;
}

void VertexArray::Unbind() {
        assert(m_Initialised && m_Bound && "VertexArray is already unbound or not Initialised");
        glBindVertexArray(0);
        m_Bound = false;
}

void VertexArray::ConnectLayoutToBuffer(VertexBuffer& buffer, const VertexBufferLayout& layout) {
        assert(m_Initialised && m_Bound && "VertexArray is already bound or not Initialised");

        if(!buffer.IsBound())
                buffer.Bind();

        std::vector<VertexBufferAttribute> attributes { layout.GetAttributes() };
        const unsigned int elementSize { layout.GetElementSize() };
        unsigned int stride { 0 };
        for(unsigned int i{}; i < attributes.size(); i++) {
                const VertexBufferAttribute& attrib { attributes[i] };
                glVertexAttribPointer(
                        i,
                        attrib.ElementAmount, 
                        attrib.Type, 
                        attrib.Normalized, 
                        elementSize, 
                        (const void*)(uintptr_t)stride
                );
                glEnableVertexAttribArray(i);
                stride += getSizeOfType(attrib.Type) * attrib.ElementAmount;
        }
}

VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &m_ArrayId);
}
