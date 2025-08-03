#include "Utils.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cassert>
#include <glm/fwd.hpp>
#include <regex>
#include <vector>

#include "Config.h"
#include "Cube.h"
#include "Face.h"


void loadWithGlad() {
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		assert(false && "Failed loading function ptrs with glad");
	}
}

std::vector<std::string> split(std::string s, const std::string& delimiter) {
	std::vector<std::string> tokens;
	int pos = 0;
	std::string token;

	while ((pos = s.find(delimiter)) != std::string::npos) {
		token = s.substr(0, pos);
		tokens.push_back(token);
		s.erase(0, pos + delimiter.length());
	}

	tokens.push_back(s);

	return tokens;
}

unsigned int getSizeOfType(GLenum type) {
        switch(type) {
        case GL_FLOAT:
        case GL_UNSIGNED_INT:
                return 4;
        default:
                assert("Undefined GLenum type. Cant get size of that type!");
                return 0;
        }
}
