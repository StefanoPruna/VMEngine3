#pragma once
#include "SDL2/SDL.h"

class Input
{
public:
	Input();

	//User's input
	void ProcessInput();

	//detect if a specific key is down
	bool IsKeyDown(SDL_Scancode Key);

private:
	const Uint8* KeyboardState;
};