#include "VMEngine/Input.h"
#include "VMEngine/Game.h"
#include <iostream>

using namespace std;

Input::Input()
{
	//assign the current keys by default
	KeyboardState = SDL_GetKeyboardState(NULL);
	MouseXDelta = MouseYDelta = 0;
	ScrollDelta = 0;
	MouseX = MouseY = 0;
}

void Input::ProcessInput()
{
	//reset the Delta each frame
	MouseXDelta = MouseYDelta = 0;
	ScrollDelta = 0;

	//Handle Input
	SDL_Event PollEvent;

	//Using ampisand
	while (SDL_PollEvent(&PollEvent))
	{
		switch (PollEvent.type)
		{
			//Update all the Mouse keys 
		case SDL_MOUSEBUTTONDOWN:
			SetMouseButtonStates(PollEvent.button.button, true);
			break;
		case SDL_MOUSEBUTTONUP:
			SetMouseButtonStates(PollEvent.button.button, false);
			break;
		case SDL_MOUSEMOTION:
			OnMouseMove(PollEvent.motion);
			break;
		case SDL_MOUSEWHEEL:
			OnMouseScroll(PollEvent.wheel);
			break;
			//update all the keys on the keyboard with up or down
		case SDL_KEYDOWN :
			KeyboardState = SDL_GetKeyboardState(NULL);
			break;
		case SDL_KEYUP :
			KeyboardState = SDL_GetKeyboardState(NULL);
			break;
		case SDL_QUIT :
			Game::GetGameInstance().CloseApp();
			break;
		default:
			break;
		}
	}
}

bool Input::IsKeyDown(SDL_Scancode Key)
{
	//make sure the keyboard state is set
	if (KeyboardState == nullptr)
	{
		cout << "No Keyboard state detected" << endl;
		return false;
	}

	//return the result of the key
	return static_cast<bool>(KeyboardState[Key]);
}

bool Input::IsMouseButtonDown(MouseButtons Button)
{
	return MouseButtonStates[Button];
}

void Input::SetMouseButtonStates(Uint8 ButtonIndex, bool CurrentState)
{
	MouseButtonStates[ButtonIndex] = CurrentState;
}

void Input::OnMouseMove(SDL_MouseMotionEvent& MEvent)
{
	//mouse position
	MouseX = MEvent.x;
	MouseY = MEvent.y;

	//movement of the mouse based on the last position
	//the relative movement
	MouseXDelta += MEvent.xrel;
	MouseYDelta += MEvent.yrel;
}

void Input::OnMouseScroll(SDL_MouseWheelEvent& MEvent)
{
	//increase the Delta relative to how much was scrolled
	ScrollDelta += MEvent.preciseY;
}
