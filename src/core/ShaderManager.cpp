#include "ShaderManager.h"

#include <cassert>

#include "ShaderUtils.h"

ShaderManager::ShaderManager(const std::string& path)
    : m_ShaderSource(getShaderSource(path))
{
}

ShaderManager::~ShaderManager()
{
	glDeleteProgram(m_ShaderProgram);
}

void ShaderManager::CreateShaderProgram()
{
	GLuint vertexShader = compileShader(GL_VERTEX_SHADER, m_ShaderSource.SourceCodeVertex.c_str());
	GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, m_ShaderSource.SourceCodeFragment.c_str());
	m_ShaderProgram = glCreateProgram();

	glAttachShader(m_ShaderProgram, vertexShader);
	glAttachShader(m_ShaderProgram, fragmentShader);
	glLinkProgram(m_ShaderProgram);

	CheckShaderProgramErrors();

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void ShaderManager::CheckShaderProgramErrors() const
{
	int success;
	glGetProgramiv(m_ShaderProgram, GL_LINK_STATUS, &success);

	if (!success) {
		char infoLog[512];
		glGetProgramInfoLog(m_ShaderProgram, 512, nullptr, infoLog);
		std::cerr << "ERROR: Shader linking failed:\n"
		          << infoLog << std::endl;
		assert(false);
	}
}

void ShaderManager::UseShaderProgram() const
{
	glUseProgram(m_ShaderProgram);
}
