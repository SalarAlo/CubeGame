// 3rd Party
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>

// standard
#include <filesystem>
#include <iostream>
#include <vector>

// own
#include "Camera.h"
#include "ChunkBuilder.h"
#include "Face.h"
#include "ScreenWindow.h"
#include "ShaderManager.h"
#include "ShaderUtils.h"
#include "ShaderWriter.h"
#include "Utils.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

/*
static constexpr float vertices[] {
        // positions           colors
        -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, // red
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // green
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // blue
        -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f, // yellow
        -0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 1.0f, // magenta
        0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, // cyan
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, // white
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f // black
};
*/

static constexpr unsigned int indices[] {
        0, 1, 2, 2, 3, 0, // back
        4, 5, 6, 6, 7, 4, // front
        4, 5, 1, 1, 0, 4, // bottom
        7, 6, 2, 2, 3, 7, // top
        4, 0, 3, 3, 7, 4, // left
        5, 1, 2, 2, 6, 5 // right
};


int main() {
        ChunkBuilder chunkBuilder(glm::ivec2(0, 0));

	ScreenWindow screenWindow(800, 800, "Rotating Cube");
	screenWindow.Init();

        // Glad must be initialized here (likely done in your ScreenWindow::Init)
        // Initialize ImGui AFTER OpenGL context creation
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        ImGui::StyleColorsDark();

        // Setup ImGui bindings
        GLFWwindow* window = screenWindow.GetGLFWWindow();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 330");

        Camera camera(45, screenWindow.GetAr(), glm::vec3(0, 0, -15));

	ShaderManager shaderManager(SHADER_PATH);
	shaderManager.CreateShaderProgram();
	unsigned int shaderProgram = shaderManager.GetShaderProgramId();

	ShaderWriter shaderWriter(shaderManager);

	VertexBuffer vertexBuffer;
	vertexBuffer.Init();

        VertexArray vertexArray;
        vertexArray.Init();

        vertexArray.Bind();

        std::vector<float> vertices = chunkBuilder.BuildChunkElementBufferData();
	vertexBuffer.Bind();
	vertexBuffer.SetData(vertices.data(), sizeof(vertices[0]) * vertices.size());

        VertexBufferLayout layout;
        layout.Push<float>(false, 3);
 
        vertexArray.ConnectLayoutToBuffer(vertexBuffer, layout);

        vertexArray.Unbind();
        vertexBuffer.Unbind();

	// Matrices location
	std::string modelMatrixName { "model" };
	std::string viewMatrixName { "view" };
	std::string projMatrixName { "projection" };

	while (!screenWindow.ShouldClose()) {
		glfwPollEvents();

                // Start ImGui frame
                ImGui_ImplOpenGL3_NewFrame();
                ImGui_ImplGlfw_NewFrame();
                ImGui::NewFrame();

                // ImGui UI
                ImGui::Begin("My First ImGui Window");
                ImGui::Text("Hello, world!");
                ImGui::End();

		glClearColor(0.1f, 0.12f, 0.15f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		shaderManager.UseShaderProgram();

		float time = (float)glfwGetTime();
		glm::mat4 model = glm::rotate(glm::mat4(1.0f), time, glm::vec3(0.5f, 1.0f, 0.0f));

		shaderWriter.WriteUniformMatrix4(modelMatrixName, model);
		shaderWriter.WriteUniformMatrix4(viewMatrixName, camera.GetView());
		shaderWriter.WriteUniformMatrix4(projMatrixName, camera.GetProjection());

                vertexArray.Bind();

                glDrawArrays(GL_TRIANGLES, 0, vertexBuffer.GetVerticesAmount());

                vertexArray.Unbind();

                ImGui::Render();
                ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(screenWindow.GetGLFWWindow());
	}

	return 0;
}
