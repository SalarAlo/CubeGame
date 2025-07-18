#pragma once

#include <iostream>
#include <cassert>
#include <string>
#include <string_view>

#include <glad/glad.h>

// internal
static constexpr auto VERTEX_SHADER_DECL_INDICATOR = "#VERTEX"; 
static constexpr auto FRAGMENT_SHADER_DECL_INDICATOR = "#FRAGMENT"; 
constexpr auto SHADER_PATH = "/home/salar/Desktop/Programming/Cpp/resources/shaders/basic.shader";

// external linkage
struct ShaderSource {
    std::string SourceCodeFragment;
    std::string SourceCodeVertex;
};

GLuint compileShader(GLenum type, const char* src);
ShaderSource getShaderSource(std::string path);
