#pragma once

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>

#include "Renderer.h"

#include <iostream>

class Window
{
private:
	int m_Width, m_Height;
	GLFWwindow* m_Window;
public:
	Renderer renderer;
	Window(int width, int height, const char* title) : m_Width(width), m_Height(height)
	{
		glfwInit();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		glfwWindowHint(GLFW_RESIZABLE, false);

		m_Window = glfwCreateWindow(m_Width, m_Height, title, NULL, NULL);
		if (m_Window == NULL)
			std::cout << "FAILED TO CREATE WINDOW" << std::endl;
		glfwMakeContextCurrent(m_Window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			std::cout << "FAILED TO INITIALIZE GLAD" << std::endl;

		renderer.Init();

		// make transparency transparent
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
	}

	GLFWwindow* GetWindow() { return m_Window; }
	int GetWidth() { return m_Width; }
	int GetHeight() { return m_Height; }

	bool ShouldClose() { return glfwWindowShouldClose(m_Window); }
	void SetShouldClose(bool value)
	{
		glfwSetWindowShouldClose(m_Window, value);
	}

	void Update()
	{
		glfwSwapBuffers(m_Window);
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT);

		//renderer.Draw(glm::vec2(0.0f, 100.0f), glm::vec2(m_Width, 75.0f));
	}

	~Window()
	{
		// destroy objects
		glfwDestroyWindow(m_Window);
		renderer.Delete();

		// terminate glfw
		glfwTerminate();
	}
};