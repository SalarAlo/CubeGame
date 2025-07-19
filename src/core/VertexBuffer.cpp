#include "VertexBuffer.h"

#include <cassert>
#include <glad/glad.h>
#include <iostream>

void VertexBuffer::Init() {
	assert(!m_Initialised && "VBO already initialised");
	glGenBuffers(1, &m_BufferId);

	m_Initialised = true;
}

void VertexBuffer::Bind() {
	assert(m_Initialised && !m_Bound && "VBO hasnt been initialised or is already bound");
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferId);

        m_Bound = true;
}

void VertexBuffer::Unbind() {
	assert(m_Initialised && m_Bound && "VBO hasnt been initialised or is already unbound");
	glBindBuffer(GL_ARRAY_BUFFER, 0);

        m_Bound = false;
}

void VertexBuffer::SetData(const float vertices[], std::size_t size) {
	assert(m_Initialised && m_Bound && "VBO hasnt been initialised or is unbound");
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer() {
	glDeleteBuffers(1, &m_BufferId);
}
