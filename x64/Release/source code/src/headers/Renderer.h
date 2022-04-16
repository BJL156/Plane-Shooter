#pragma once

#include <GLAD/glad.h>
#include <GLM/glm.hpp>
#include <GLM/GTC/matrix_transform.hpp>
#include "stb_image/stb_image.h"

#include "Shader.h"
#include "Texture.h"

class Renderer
{
private:
	Shader m_Shader;
	unsigned int m_VAO, m_VBO;
public:
	void Init()
	{
		m_Shader.Compile("res/shaders/vertex.glsl", "res/shaders/fragment.glsl");

		float vertices[] =
		{
			0.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f,

			0.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 0.0f, 1.0f, 0.0f
		};
		glGenBuffers(1, &m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void Draw(glm::vec2 position, glm::vec2 scale, Texture texture)
	{
		m_Shader.Use();

		texture.Bind();

		glm::mat4 projection = glm::ortho(0.0f, 860.0f, 600.0f, 0.0f, -1.0f, 1.0f);
		glm::mat4 model = glm::mat4(1.0f);

		model = glm::translate(model, glm::vec3(position.x, position.y, 0.0f));
		model = glm::scale(model, glm::vec3(scale.x, scale.y, 0.0f));

		m_Shader.SetMat4("projection", projection);
		m_Shader.SetMat4("model", model);

		glBindVertexArray(m_VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
	}

	void Delete()
	{
		glDeleteBuffers(1, &m_VBO);
		glDeleteVertexArrays(1, &m_VAO);

		m_Shader.Delete();
	}
};