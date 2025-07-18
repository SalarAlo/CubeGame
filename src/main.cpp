// 3rd Party
#include <GLFW/glfw3.h>
#include <glad/glad.h>
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
#include "VertexBuffer.h"

int main()
{
	ScreenWindow screenWindow(800, 600, "Rotating Cube");
	screenWindow.Init();

	VertexBuffer vertexBuffer;
	vertexBuffer.Init();

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

	GLuint VAO, EBO;
	glGenVertexArrays(1, &VAO);
	vertexBuffer.Init();
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	vertexBuffer.Bind();
	vertexBuffer.SetData(vertices, sizeof(vertices));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
	    GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
	    (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

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

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(screenWindow.GetGLFWWindow());
	}

	// Cleanup
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &EBO);

	return 0;
}
