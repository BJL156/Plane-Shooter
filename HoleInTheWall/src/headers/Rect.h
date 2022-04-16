#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Renderer.h"
#include "Texture.h"

class Rect
{
public:
	float x, y;
	float width, height;
	Rect(float X, float Y, float Width, float Height) : x(X), y(Y), width(Width), height(Height)
	{

	}

	bool IsColliding(Rect other)
	{
		if (x + width > other.x && x < other.x + other.width && y + height > other.y && y < other.y + other.height)
			return true;
		return false;
	}

	void Draw(Texture texture, Window* window)
	{
		window->renderer.Draw(glm::vec2(x, y), glm::vec2(width, height), texture);
	}
};