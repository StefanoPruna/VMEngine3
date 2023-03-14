#include "VMEngine/Game.h"

int main(int argc, char** argv) 
{
	//changing the resolution, now it's 1:1
	Game::GetGameInstance().Start("VMEngine | An OpenGl Engine", false, 720, 720);

	Game::GetGameInstance();

	Game::DestroyGameInstance();

	return 0;
}