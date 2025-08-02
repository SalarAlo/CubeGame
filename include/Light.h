#pragma once

#include "ShaderWriter.h"

class Light {
public:
        Light() = default;
        void Init(float ambient, float diffuse, float specular, glm::vec3 lightColor, glm::vec3 lightDirection);

        void WriteToShader(ShaderWriter& shaderWriter);

private:
        glm::vec3 m_LightColor {};
        glm::vec3 m_LightDirection {};
        float m_Ambient {};
        float m_Diffuse {};
        float m_Specular {};
};
