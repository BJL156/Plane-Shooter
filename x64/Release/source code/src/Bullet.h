#pragma once

#include "headers/Engine.h"

class Bullet
{
private:
	Window* m_Window;
public:
	Texture* bulletTexture = new Texture("res/textures/bullet.png");
	Rect* bullet = new Rect(0.0f, 0.0f, bulletTexture->width, bulletTexture->height);

	int initialX;
	Bullet(int x, int y, Window* window) : initialX(x), m_Window(window)
	{
		bullet->x = initialX;
		bullet->y = y;
	}

	void Update(float deltaTime)
	{
		Movement(deltaTime);
		Draw();
	}

	float speed = 500.0f;
private:
	void Movement(float deltaTime)
	{
		bullet->x += speed * deltaTime;
	}
	void Draw()
	{
		bullet->Draw((*bulletTexture), m_Window);
	}
};