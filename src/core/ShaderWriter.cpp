#include "ShaderWriter.h"

#include "ShaderManager.h"

#include <glm/gtc/type_ptr.hpp>

void ShaderWriter::WriteUniformMatrix4(const std::string& name, const glm::mat4& matrix) {
	auto location = glGetUniformLocation(m_ShaderManager->m_ShaderProgram, name.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}
