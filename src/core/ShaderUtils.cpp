#include "ShaderUtils.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <iterator>

#include "Utils.h"

ShaderSource getShaderSource(std::string path) {
	ShaderSource source;

	std::ifstream file(path, std::ios::in);
	assert(file && "Failed to open file provided in shader source");
	std::string contents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	file.close();

	auto shaderContentsSplitted {
		split(
		    (split(contents, VERTEX_SHADER_DECL_INDICATOR)[1]),
		    FRAGMENT_SHADER_DECL_INDICATOR)
	};

	source.SourceCodeVertex = shaderContentsSplitted[0];
	source.SourceCodeFragment = shaderContentsSplitted[1];

	return source;
}

GLuint compileShader(GLenum type, const char* src) {
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &src, nullptr);
	glCompileShader(shader);
	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, nullptr, infoLog);
		std::cerr << "ERROR: Shader compilation failed:\n"
		          << infoLog << "\n";
		assert(false);
	}

	return shader;
}
