// 3rd Party
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// standard
#include <filesystem>
#include <iostream>

// own
#include "ScreenWindow.h"
#include "ShaderManager.h"
#include "ShaderUtils.h"
#include "ShaderWriter.h"
#include "Utils.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"

int main() {
	ScreenWindow screenWindow(800, 600, "Rotating Cube");
	screenWindow.Init();

	ShaderManager shaderManager(SHADER_PATH);
	shaderManager.CreateShaderProgram();
	unsigned int shaderProgram = shaderManager.GetShaderProgramId();

	ShaderWriter shaderWriter(shaderManager);

	float vertices[] = {
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

	unsigned int indices[] = {
		0, 1, 2, 2, 3, 0, // back
		4, 5, 6, 6, 7, 4, // front
		4, 5, 1, 1, 0, 4, // bottom
		7, 6, 2, 2, 3, 7, // top
		4, 0, 3, 3, 7, 4, // left
		5, 1, 2, 2, 6, 5 // right
	};

	VertexBuffer vertexBuffer;
	vertexBuffer.Init();

        IndexBuffer indexBuffer;
        indexBuffer.Init();

        VertexArray vertexArray;
        vertexArray.Init();

        vertexArray.Bind();

	vertexBuffer.Bind();
	vertexBuffer.SetData(vertices, sizeof(vertices));

        indexBuffer.Bind();
        indexBuffer.FillData(indices, sizeof(indices));

        VertexBufferLayout layout;
        layout.Push<float>(false, 3);
        layout.Push<float>(false, 3);
 
        vertexArray.ConnectLayoutToBuffer(vertexBuffer, layout);

        vertexArray.Unbind();
        indexBuffer.Unbind();
        vertexBuffer.Unbind();

	// Matrices location
	std::string modelMatrixName { "model" };
	std::string viewMatrixName { "view" };
	std::string projMatrixName { "projection" };

	// Projection matrix (perspective)
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.f / 600.f, 0.1f, 100.0f);

	while (!screenWindow.ShouldClose()) {
		glfwPollEvents();

		glClearColor(0.1f, 0.12f, 0.15f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderManager.UseShaderProgram();

		// Rotate over time
		float time = (float)glfwGetTime();
		glm::mat4 model = glm::rotate(glm::mat4(1.0f), time, glm::vec3(0.5f, 1.0f, 0.0f));
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));

		shaderWriter.WriteUniformMatrix4(modelMatrixName, model);
		shaderWriter.WriteUniformMatrix4(viewMatrixName, view);
		shaderWriter.WriteUniformMatrix4(projMatrixName, projection);

                vertexArray.Bind();

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

                vertexArray.Unbind();

		glfwSwapBuffers(screenWindow.GetGLFWWindow());
	}


	return 0;
}
