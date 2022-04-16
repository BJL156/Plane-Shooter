#pragma once

#include "headers/Engine.h"

#include "Obstacle.h"
#include "Bullet.h"

#include <vector>

class Plane
{
private:
	Window* m_Window;
public:
	Texture* planeTexture = new Texture("res/textures/plane.png");
	Rect* plane = new Rect(0.0f, 0.0f, planeTexture->width * 5, planeTexture->height * 5);

	std::vector<Bullet> bullets;

	Plane(Window* window) : m_Window(window)
	{

	}

	bool mouseDown = false;
	void Update(Sound soundEngine, float deltaTime)
	{
		if (mouseDown == false)
		{
			if (speed > 0.0f)
			{
				if (Input::IsMouseButtonDown(m_Window, GAME_MOUSE_BUTTON_1))
				{
					soundEngine.Play("res/audio/shoot.mp3", false);
					bullets.push_back(Bullet(plane->x + plane->width / 2, plane->y + plane->height / 2, m_Window));
					mouseDown = true;
				}
			}
		}
		else
		{
			if (Input::IsMouseButtonUp(m_Window, GAME_MOUSE_BUTTON_1))
			{
				mouseDown = false;
			}
		}

		Movement(deltaTime);
		Draw(deltaTime);
	}

	float speed = 1000.0f;
private:
	void Movement(float deltaTime)
	{
		if ((Input::IsKeyDown(m_Window, GAME_KEY_W) || Input::IsKeyDown(m_Window, GAME_KEY_UP)) && plane->y > 0.0f)
			plane->y -= speed * deltaTime;
		if ((Input::IsKeyDown(m_Window, GAME_KEY_A) || Input::IsKeyDown(m_Window, GAME_KEY_LEFT)) && plane->x > 0.0f)
			plane->x -= speed * deltaTime;
		if ((Input::IsKeyDown(m_Window, GAME_KEY_S) || Input::IsKeyDown(m_Window, GAME_KEY_DOWN)) && plane->y < m_Window->GetHeight() - plane->height)
			plane->y += speed * deltaTime;
		if ((Input::IsKeyDown(m_Window, GAME_KEY_D) || Input::IsKeyDown(m_Window, GAME_KEY_RIGHT)) && plane->x < m_Window->GetWidth() - plane->width)
			plane->x += speed * deltaTime;
	}
	void Draw(float deltaTime)
	{
		for (int i = 0; i < bullets.size(); i++)
		{
			bullets[i].Update(deltaTime);
		}
		plane->Draw((*planeTexture), m_Window);
	}
};