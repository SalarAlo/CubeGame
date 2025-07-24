#include "Utils.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cassert>
#include <regex>
#include <vector>

#include "Config.h"
#include "Face.h"

glm::vec3 getRgbForColor(MeshColor color) {
    switch (color) {
        case Red:     return {1.0f, 0.0f, 0.0f};
        case Green:   return {0.0f, 1.0f, 0.0f};
        case Blue:    return {0.0f, 0.0f, 1.0f};
        case Yellow:  return {1.0f, 1.0f, 0.0f};
        case Cyan:    return {0.0f, 1.0f, 1.0f};
        case Magenta: return {1.0f, 0.0f, 1.0f};
        case White:   return {1.0f, 1.0f, 1.0f};
        default:      return {0.0f, 0.0f, 0.0f};  // fallback: black
    }
}
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

std::string directionToString(Direction direction) {
        switch(direction) {
        case Direction::Top:
                return std::string { "Top" };
        case Direction::Bottom:
                return std::string { "Bottom" };
        case Direction::Right:
                return std::string { "Right" };
        case Direction::Left:
                return std::string { "Left" };
        case Direction::Forward:
                return std::string { "Forward" };
        case Direction::Back:
                return std::string { "Back" };
        default:
                assert(false && "Unhandled case for direction to string conversion");
                return std::string { "" };
        }
}
