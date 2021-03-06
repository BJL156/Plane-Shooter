#pragma once

#include <GLAD/glad.h>
#include "stb_image/stb_image.h"

#include <iostream>

class Texture
{
public:
	unsigned texture;
	int width, height;
	Texture(const char* filePath)
	{

		int nrChannels;
		unsigned char* data = stbi_load(filePath, &width, &height, &nrChannels, 0);

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		// wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		// filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
			std::cout << "FAILED TO LOAD TEXTURE" << std::endl;
		stbi_image_free(data);
	}

	void Bind()
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
	}
};