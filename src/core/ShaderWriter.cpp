#include "ShaderWriter.h"

#include "ShaderManager.h"
#include "ShaderUtils.h"

#include <glm/gtc/type_ptr.hpp>

void ShaderWriter::WriteUniformMatrix4(const std::string& name, const glm::mat4& matrix) {
	auto location = glGetUniformLocation(m_ShaderManager->m_ShaderProgram, name.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void ShaderWriter::WriteUniformFloat(const std::string& name, float value) {
	auto location = glGetUniformLocation(m_ShaderManager->m_ShaderProgram, name.c_str());
	glUniform1f(location, value);
}

void ShaderWriter::WriteUniformVec3(const std::string& name, glm::vec3 vector) {
	auto location = glGetUniformLocation(m_ShaderManager->m_ShaderProgram, name.c_str());
	glUniform3f(location, vector.x, vector.y, vector.z);
}
