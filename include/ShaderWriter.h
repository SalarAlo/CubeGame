#pragma once

#include <glm/fwd.hpp>
#include <glm/mat4x4.hpp>
#include <string>

class ShaderManager;

class ShaderWriter {
public:
    ShaderWriter(ShaderManager& shaderManager) : m_ShaderManager(shaderManager) {};
    void WriteUniformMatrix4(const std::string& name, const glm::mat4& matrix);
private:
    ShaderManager& m_ShaderManager;
};
