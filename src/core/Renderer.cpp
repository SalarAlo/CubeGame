#include "Renderer.h"

#include "ScreenWindow.h"
#include "ShaderUtils.h"
#include "VertexBufferLayout.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <glm/trigonometric.hpp>


void Renderer::Init() {
        InitCam();
        InitShader();
        InitBuffers();
}

void Renderer::InitCam() {
        float degree { glm::radians(20.0f) };
        float fov { 45.0f };

        m_Camera.Init(
                fov, 
                ScreenWindow::GetInstance().GetAr(), 
                glm::vec3(0, 20, -30),
                glm::vec3(0, -glm::sin(degree), glm::cos(degree))
        );
}

void Renderer::BeginFrame() {
        glClearColor(0.1f, 0.12f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_ShaderManager.UseShaderProgram();

	const std::string modelMatrixName { "model" };
	const std::string viewMatrixName { "view" };
	const std::string projMatrixName { "projection" };

        float time = (float)glfwGetTime();
        glm::mat4 model = glm::rotate(glm::mat4(1.0f), time, glm::vec3(0, 1.0f, 0.0f));

        m_ShaderWriter.WriteUniformMatrix4(modelMatrixName, model);
        m_ShaderWriter.WriteUniformMatrix4(viewMatrixName, m_Camera.GetView());
        m_ShaderWriter.WriteUniformMatrix4(projMatrixName, m_Camera.GetProjection());
}

void Renderer::DrawFrame() {
        m_VertexArray.Bind();
        glDrawArrays(GL_TRIANGLES, 0, m_VertexBuffer.GetVerticesAmount());
        m_VertexArray.Unbind();
}

void Renderer::SetupBufferForDraw(const ChunkBuilder& chunkBuilder) {
        m_VertexArray.Bind();
        m_VertexBuffer.Bind();

        auto vertices = chunkBuilder.BuildChunkElementBufferData();
	m_VertexBuffer.SetData(vertices.data(), sizeof(vertices[0]) * vertices.size());

        m_VertexArray.Unbind();
        m_VertexBuffer.Unbind();
}

void Renderer::EndFrame() {
	glfwSwapBuffers(ScreenWindow::GetInstance().GetGLFWWindow());
}

void Renderer::InitShader(){
	m_ShaderManager.Init(SHADER_PATH);
	m_ShaderManager.CreateShaderProgram();

	m_ShaderWriter.SetShaderManager(m_ShaderManager);
}

void Renderer::InitBuffers() {
        m_VertexArray.Init();
        m_VertexBuffer.Init();

        m_VertexArray.Bind();
        m_VertexBuffer.Bind();

        VertexBufferLayout layout;
        layout.Push<float>(false, 3);
        layout.Push<float>(false, 3);

        m_VertexArray.ConnectLayoutToBuffer(m_VertexBuffer, layout);

        m_VertexArray.Unbind();
        m_VertexBuffer.Unbind();
}

