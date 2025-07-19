#include "IndexBuffer.h"

#include <glad/glad.h>
#include <cassert>

void IndexBuffer::Init() {
	assert(!m_Initiliased && "Index buffer initiliased");
	m_Initiliased = true;
	glGenBuffers(1, &m_BufferId);
}

void IndexBuffer::Bind() {
	assert(m_Initiliased && !m_Bound && "Index Buffer not initiliased or already bound");
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferId);
        m_Bound = true;
}

void IndexBuffer::Unbind() {
	assert(m_Initiliased && m_Bound && "Index Buffer not initiliased or already unbound");
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        m_Bound = false;
}

void IndexBuffer::FillData(const unsigned int indices[], std::size_t size) {
	assert(m_Initiliased && m_Bound && "Index Buffer not initiliased or already unbound");
        m_ElementCount = static_cast<unsigned int>(size) / sizeof(unsigned int);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() {
	glDeleteBuffers(1, &m_BufferId);
}
