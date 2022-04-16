#pragma once

#include "headers/Engine.h"

#include <random>

class Obstacle
{
private:
	Window* m_Window;
public:
	Texture* obstacleTexture = new Texture("res/textures/ground.png");

	const float startTime = 300.0f;

	Rect* bottom = new Rect(m_Window->GetWidth() + startTime, m_Window->GetHeight() - obstacleTexture->height * 5.0f + 300.0f, obstacleTexture->width * 5.0f, obstacleTexture->height * 5.0f);
	Rect* top = new Rect(m_Window->GetWidth() + startTime, -300.0f, obstacleTexture->width * 5.0f, obstacleTexture->height * 5.0f);

	Texture* boxTexture = new Texture("res/textures/box.png");
	Rect* box = new Rect(top->x, top->y + top->height + 10.0f, boxTexture->width * 5.0f, boxTexture->height * 5.0f);

	void RandomHeight()
	{
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> dist6(200, m_Window->GetHeight());

		bottom->y = dist6(rng);
		top->y = bottom->y - box->height - top->height;

		box->y = top->y + top->height + 10.0f;

		std::cout << dist6(rng) << std::endl;
	}

	Obstacle(Window* window) : m_Window(window)
	{
		RandomHeight();
	}

	void Update(float deltaTime)
	{
		Movement(deltaTime);
		Draw();
	}

	float speed = 1000.0f;
private:
	void Movement(float deltaTime)
	{
		if (bottom->x + bottom->width < 0.0f)
		{
			RandomHeight();
			bottom->x = m_Window->GetWidth();
			box->y = top->y + top->height + 10.0f;
		}
		bottom->x -= speed * deltaTime;
		top->x = bottom->x;

		box->x = top->x + top->width / 2 - box->width / 2;
	}
	void Draw()
	{
		top->Draw((*obstacleTexture), m_Window);
		bottom->Draw((*obstacleTexture), m_Window);

		box->Draw((*boxTexture), m_Window);
	}
};