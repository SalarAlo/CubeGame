#pragma once

#include "Camera.h"
#include "Light.h"
#include "ScreenWindow.h"
#include "ChunkBuilder.h"

#include "ShaderManager.h"
#include "ShaderUtils.h"
#include "ShaderWriter.h"


#include "VertexArray.h"
#include "VertexBuffer.h"

class Renderer { 
public:
        void Init(int renderWidth, int renderHeight, int x = 0, int y = 0);

        void BeginFrame();
        void DrawFrame();
        void EndFrame();
        void SetupBufferForDraw(const ChunkBuilder& chunkBuilder);

        inline void SetLight(const Light& light) { m_Light = light; }
private:
        void InitCam();
        void InitShader();
        void InitBuffers();
        void SetRenderRegion(int x, int y, int width, int height);

private:
        ShaderManager m_ShaderManager {};
        ShaderWriter m_ShaderWriter {};   

        VertexBuffer m_VertexBuffer {};
        VertexArray m_VertexArray {};

        Camera m_Camera {};
        Light m_Light {};

        int m_X {}; 
        int m_Y {}; 
        int m_Width {}; 
        int m_Height {};
};
