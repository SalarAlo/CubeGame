#pragma once

#include <string>

#include "ShaderUtils.h"
#include "ShaderWriter.h"

// Make Singleton
class ShaderManager {
friend ShaderWriter;
public:
        ShaderManager() = default;
        void Init(const std::string& path);

        void CreateShaderProgram();
        void UseShaderProgram() const;
        ~ShaderManager();
    
        inline unsigned int GetShaderProgramId() const { return m_ShaderProgram; }
private:
        void CheckShaderProgramErrors() const;

private:
        ShaderSource m_ShaderSource {};
        unsigned int m_ShaderProgram { 0 };
};

