#pragma once

#include "Face.h"
#include <string>
#include <vector>
#include <glad/glad.h>

#include <glm/glm.hpp>

void loadWithGlad();
std::vector<std::string> split(std::string s, const std::string& delimiter);
unsigned int getSizeOfType(GLenum type);
