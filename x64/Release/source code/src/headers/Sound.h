#pragma once

#include <irrklang.h>

using namespace irrklang;

class Sound
{
private:
	ISoundEngine* soundEngine = createIrrKlangDevice();
	irrklang::ISound* sound;
public:
	void Play(const char* filePath, bool repeat)
	{
		sound = soundEngine->play2D(filePath, repeat);
	}

	float GetVolume() { return soundEngine->getSoundVolume(); }
	void SetVolume(float value)
	{
		soundEngine->setSoundVolume(value);
	}
};