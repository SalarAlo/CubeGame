#pragma once

#include <glm/fwd.hpp>
#include <glm/mat4x4.hpp>
#include <string>

class ShaderManager;

class ShaderWriter {
public:
        ShaderWriter() = default;
        inline void SetShaderManager(ShaderManager& shaderManager) { m_ShaderManager = &shaderManager; }
        void WriteUniformMatrix4(const std::string& name, const glm::mat4& matrix);
        void WriteUniformFloat(const std::string& name, float value);
        void WriteUniformVec3(const std::string& name, glm::vec3 vector);
private:
        ShaderManager* m_ShaderManager { };
};
