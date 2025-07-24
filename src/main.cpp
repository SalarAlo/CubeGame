// 3rd Party
#include <cstdlib>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// standard
#include <filesystem>
#include <iostream>
#include <vector>

// own
#include "Camera.h"
#include "ChunkBuilder.h"
#include "Constants.h"
#include "Cube.h"
#include "Face.h"
#include "ImGuiView.h"
#include "ScreenWindow.h"
#include "ShaderManager.h"
#include "ShaderUtils.h"
#include "ShaderWriter.h"
#include "Utils.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

int main() {
        ChunkBuilder chunkBuilder(glm::ivec2(0, 0));

        chunkBuilder.AddCube(Cube { glm::vec3(0, 0, 0), MeshColor::Cyan });

	ScreenWindow screenWindow(800, 800, "Rotating Cube");
	screenWindow.Init();

        ImGuiView::getInstance().Init(screenWindow);

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

        ImGuiView::getInstance().SetOnCompileCallback([vertices](){
                int verticesCount = vertices.size();
                for(int i {}; i < verticesCount; i++) {
                        std::cout << vertices[i];
                        std::cout << (((i + 1) % (VALUES_PER_VERTEX) == 0) ? "\n" : ", ");
                        std::cout << std::flush;
                }
        });

	vertexBuffer.Bind();
	vertexBuffer.SetData(vertices.data(), sizeof(vertices[0]) * vertices.size());

        VertexBufferLayout layout;
        layout.Push<float>(false, 3);
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

                ImGuiView::getInstance().SetupUI();

		glClearColor(0.1f, 0.12f, 0.15f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		shaderManager.UseShaderProgram();

		float time = (float)glfwGetTime();
		glm::mat4 model = glm::rotate(glm::mat4(1.0f), time, glm::vec3(0, 1.0f, 0.0f));

		shaderWriter.WriteUniformMatrix4(modelMatrixName, model);
		shaderWriter.WriteUniformMatrix4(viewMatrixName, camera.GetView());
		shaderWriter.WriteUniformMatrix4(projMatrixName, camera.GetProjection());

                vertexArray.Bind();

                glDrawArrays(GL_TRIANGLES, 0, vertexBuffer.GetVerticesAmount());

                vertexArray.Unbind();

                ImGuiView::getInstance().DrawUI();

		glfwSwapBuffers(screenWindow.GetGLFWWindow());
	}

	return 0;
}
