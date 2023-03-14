#include "VMEngine/Input.h"
#include "VMEngine/Game.h"
#include <iostream>

using namespace std;

Input::Input()
{
	//assign the current keys by default
	KeyboardState = SDL_GetKeyboardState(NULL);
}

void Input::ProcessInput()
{
	SDL_Event PollEvent;

	//Using ampisand
	while (SDL_PollEvent(&PollEvent))
	{
		switch (PollEvent.type)
		{
			//update all the keys on the keyboard with up or down
		case SDL_KEYDOWN :
			KeyboardState = SDL_GetKeyboardState(NULL);
			break;
		case SDL_KEYUP :
			KeyboardState = SDL_GetKeyboardState(NULL);
			break;
		case SDL_QUIT:
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
