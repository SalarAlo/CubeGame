#pragma once

#include "Camera.h"
#include "ScreenWindow.h"
#include "ChunkBuilder.h"

#include "ShaderManager.h"
#include "ShaderUtils.h"
#include "ShaderWriter.h"


#include "VertexArray.h"
#include "VertexBuffer.h"

class Renderer { 
public:
        void Init();

        void BeginFrame();
        void DrawFrame();
        void EndFrame();
        void SetupBufferForDraw(const ChunkBuilder& chunkBuilder);

private:
        void InitCam();
        void InitShader();
        void InitBuffers();
private:
        ShaderManager m_ShaderManager {};
        ShaderWriter m_ShaderWriter {};   

        VertexBuffer m_VertexBuffer {};
        VertexArray m_VertexArray {};

        Camera m_Camera {};
};
