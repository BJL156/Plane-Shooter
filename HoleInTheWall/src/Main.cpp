#include "headers/Engine.h"

#include "Plane.h"
#include "Obstacle.h"

#include <windows.h>

#include <iostream>

int main()
{
	Window window(860, 600, "Hole in The Wall");

	Sound soundEngine;

	Plane plane(&window);
	Obstacle obstacle(&window);

	Texture backgroundTexture("res/textures/background.png");
	Rect background(0.0f, 0.0f, backgroundTexture.width * 5, backgroundTexture.height * 5);

	float deltaTime = 0.0f;
	float lastTime = 0.0f;

	float playedDeathSound = false;

	while (!window.ShouldClose())
	{
		deltaTime = glfwGetTime() - lastTime;
		lastTime = glfwGetTime();


		window.Update();


		if (plane.plane->IsColliding((*obstacle.top)) || plane.plane->IsColliding((*obstacle.bottom)) || plane.plane->IsColliding((*obstacle.box)))
		{
			plane.speed = 0.0f;
			obstacle.speed = 0.0f;
			if (!playedDeathSound)
				soundEngine.Play("res/audio/death.mp3", false);
			playedDeathSound = true;
		}

		for (int i = 0; i < plane.bullets.size(); i++)
		{
			if (plane.bullets[i].bullet->IsColliding((*obstacle.box)))
			{
				obstacle.box->y = -obstacle.box->height;
				plane.bullets.erase(plane.bullets.begin() + i);
			}
			if (plane.bullets[i].bullet->x > plane.bullets[i].initialX + 300.0f || plane.bullets[i].bullet->x > window.GetWidth() || plane.speed == 0.0f)
			{
				plane.bullets.erase(plane.bullets.begin() + i);
			}
		}

		background.Draw(backgroundTexture, &window);

		plane.Update(soundEngine, deltaTime);
		obstacle.Update(deltaTime);
	}
}