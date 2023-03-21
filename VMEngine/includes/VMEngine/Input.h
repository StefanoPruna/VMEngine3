#pragma once
#include "SDL2/SDL.h"

enum MouseButtons
{
	LEFT = SDL_BUTTON_LEFT,
	MIDDLE = SDL_BUTTON_MIDDLE,
	RIGHT = SDL_BUTTON_RIGHT
};

class Input
{
public:
	Input();

	//User's input
	void ProcessInput();

	//detect if a specific key is down
	bool IsKeyDown(SDL_Scancode Key);

	//detect if the mouse button inputed is being pressed down
	bool IsMouseButtonDown(MouseButtons Button);

	//mouse position
	int MouseX, MouseY;

	//how far the mouse has moved since the last check/tick
	int MouseXDelta, MouseYDelta;

	//how far the player has scrolled since the last frame
	float ScrollDelta;

private:
	//keyboard current states
	const Uint8* KeyboardState;

	//mouse button current states
	bool MouseButtonStates[10] = { false };

	void SetMouseButtonStates(Uint8 ButtonIndex, bool CurrentState);

	//it'll handle the vars that rely on mouse motion
	void OnMouseMove(SDL_MouseMotionEvent& MEvent);

	//handle the vars that rely on the scroll of the mouse
	void OnMouseScroll(SDL_MouseWheelEvent& MEvent);
};