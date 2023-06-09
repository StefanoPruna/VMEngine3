#pragma once
#include "VMEngine/CoreMinimal.h"

class Input;

class Game
{
public:
	//Get the game instance or create one if it doesn't exit
	static Game& GetGameInstance();

	//Destroy the game running the destructor
	//Void because we don't want to return any values
	static void DestroyGameInstance();

	void Start(const char* WTitle, bool bFullscreen, int WWidth, int WHeight);

	//get delta time precisly
	double GetDeltaTime() { return DeltaTime; }

	//get delta time less precisly
	float GetFDeltaTime() { return static_cast<float>(DeltaTime); }

	//return the graphic engine
	GraphicsEnginePtr GetGraphicsEngine() { return Graphics; }

	//set the bIsGameOver to true
	void CloseApp() { bIsGameOver = true; }

	//return the graphics engine default texture
	TexturePtr GetDefaultEngineTexture();

	//return the graphics engine default material
	MaterialPtr GetDefaultEngineMaterial();

	//remove a model from everywhere in the game and graphic engine
	void RemoveModelFromGame(ModelPtr& ModelToRemove);

private:
	Game();
	~Game();

	void Run();

	//Handle the Input
	void ProcessInput();

	//Does the logic/Output
	void Update();

	//Drawing the graphics to the screen
	void Draw();

	//Anything that needs to be deleted at the end of the game
	void CloseGame();

	//boolean that ends the game
	bool bIsGameOver;

	GraphicsEnginePtr Graphics;

	//time between frames, double is more precised than float
	double DeltaTime;

	//read the input of the player
	Input* GameInput;

	//temp mesh variables
	ModelPtr RedCoin;
	ModelPtr GoldCoin;
	ModelPtr Background;
	ModelPtr Wall;
	ModelPtr Wall2;
	ModelPtr Wall3;
	ModelPtr Wall4;
	ModelPtr Wall5;
};