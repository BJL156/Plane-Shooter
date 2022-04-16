#pragma once

#include <GLAD/glad.h>

#include <fstream>
#include <sstream>
#include <string>

#include <iostream>

class Shader
{
public:
	unsigned int ID;
	void Compile(const char* vertexPath, const char* fragmentPath)
	{
		// vertex shader source
		std::fstream vertexFile;
		std::stringstream vertexStream;

		vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			vertexFile.open(vertexPath);
			vertexStream << vertexFile.rdbuf();
			vertexFile.close();
		}
		catch (std::ifstream::failure exception)
		{
			std::cout << "FAILED TO READ VERTEX SHADER FILE" << std::endl;
		}

		std::string vertexString = vertexStream.str();
		const char* vertexShaderSource = vertexString.c_str();

		// fragment shader source
		std::fstream fragmentFile;
		std::stringstream fragmentStream;

		fragmentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			fragmentFile.open(fragmentPath);
			fragmentStream << fragmentFile.rdbuf();
			fragmentFile.close();
		}
		catch (const std::exception&)
		{
			std::cout << "FAILED TO READ FRAGMENT SHADER FILE" << std::endl;
		}

		std::string fragmentString = fragmentStream.str();
		const char* fragmentShaderSource = fragmentString.c_str();


		// create shader program
		std::cout << vertexStream.str() << std::endl;
		std::cout << std::endl;
		std::cout << fragmentStream.str() << std::endl;

		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);

		unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);

		ID = glCreateProgram();
		glAttachShader(ID, vertexShader);
		glAttachShader(ID, fragmentShader);
		glLinkProgram(ID);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	void Use()
	{
		glUseProgram(ID);
	}

	// set uniforms
	void SetVec3(std::string name, glm::vec3 vec3)
	{
		glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &vec3[0]);
	}
	void SetMat4(std::string name, glm::mat4 mat4)
	{
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat4[0][0]);
	}

	void Delete()
	{
		glDeleteProgram(ID);
	}
};