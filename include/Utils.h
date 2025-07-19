#pragma once

#include <string>
#include <vector>
#include <glad/glad.h>

void loadWithGlad();
std::vector<std::string> split(std::string s, const std::string& delimiter);
unsigned int getSizeOfType(GLenum type);
