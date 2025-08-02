#include "Light.h"
#include <string>

void Light::Init(float ambient, float diffuse, float specular, glm::vec3 lightColor, glm::vec3 lightDirection) {
        m_Ambient = ambient;
        m_Diffuse = diffuse;
        m_Specular = specular;
        m_LightColor = lightColor;
        m_LightDirection = lightDirection;
}


void Light::WriteToShader(ShaderWriter& shaderWriter) {
        const std::string ambientName { "u_Light.Ambient"};
        const std::string diffuseName { "u_Light.Diffuse"};
        const std::string specularName { "u_Light.Specular"};
        const std::string lightColorName { "u_Light.Color"};
        const std::string lightDirection { "u_Light.Direction"};

        shaderWriter.WriteUniformFloat(ambientName, m_Ambient);
        shaderWriter.WriteUniformFloat(diffuseName, m_Diffuse);
        shaderWriter.WriteUniformFloat(specularName, m_Specular);
        shaderWriter.WriteUniformVec3(lightColorName, m_LightColor);
        shaderWriter.WriteUniformVec3(lightDirection, m_LightDirection);
}

