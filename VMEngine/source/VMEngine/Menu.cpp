#include "VMEngine/Menu.h"
#include "VMEngine/Game.h"
#include "SDL2/SDL_syswm.h"
#include "VMEngine/resource.h"
#include <iostream>

using namespace std;

Menu::Menu()
{
	_window = FindWindow(NULL, NULL);
	if (_window == NULL)
	{
		cout << "Failed to find window\n";
		exit(1);
	}
	_menu = LoadMenu(GetModuleHandle(0), MAKEINTRESOURCE(IDR_MENU1));
	if (_menu == NULL)
	{
		cout << "Failed to create menu";
		exit(1);
	}
	if (SetMenu(_window, _menu) == 0)
		cout << "Failed to create menu";

	Uint8 event_state_result = SDL_EventState(SDL_SYSWMEVENT, SDL_ENABLE);
	Uint8 event_state_success = SDL_DISABLE;
	if (event_state_success != event_state_result)
	{
		cout << "Failed to enable";
		exit(1);
	}
}

void Menu::getMenu()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_SYSWMEVENT:
			if (event.syswm.msg->msg.win.wParam == ID_FILE_NEWWINDOW)
			{
				cout << "ID_FILE_NEWWINDOW = " << ID_FILE_NEWWINDOW << "\n";

				if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
				{
					sdlWindow2 = SDL_CreateWindow("Sub Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
					//render for window
					m_Renderer2 = SDL_CreateRenderer(sdlWindow2, 0, -1);
				}
			}
			else if (event.syswm.msg->msg.win.wParam == ID_FILE_EXIT)
			{
				cout << "ID_FILE_EXIT = " << ID_FILE_EXIT << "\n";
				SDL_DestroyWindow(sdlWindow2);
				SDL_DestroyRenderer(m_Renderer2);
			}
			else if (event.syswm.msg->msg.win.wParam == ID_HELP_ABOUTGAME)
			{
				cout << "ID_HELP_ABOUTGAME = " << ID_HELP_ABOUTGAME << "\n";
				DisplayDialogBox();
			}
			break;
		}
	}
}

int Menu::DisplayDialogBox()
{
	int msgboxID = MessageBox(NULL, NULL, NULL, MB_ICONEXCLAMATION | MB_OK);
	//return msgboxID;
	return true;
}
