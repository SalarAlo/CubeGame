#include "IndexBuffer.h"

#include <cassert>
#include <glad/glad.h>

void IndexBuffer::Init()
{
	assert(!m_Initiliased && "Index buffer initiliased");
	m_Initiliased = true;
	glGenBuffers(1, &m_BufferId);
}

void IndexBuffer::Bind()
{
	assert(m_Initiliased && !m_Bound && "Index Buffer not initiliased or already bound");
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferId);
}

void IndexBuffer::Unbind()
{
	assert(m_Initiliased && m_Bound && "Index Buffer not initiliased or already unbound");
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
