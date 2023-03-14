#include "VMEngine/Game.h"
#include "VMEngine/Graphics/GraphicsEngine.h"
#include "VMEngine/Graphics/ShaderProgram.h"
#include "VMEngine/Graphics/Texture.h"
#include "VMEngine/Graphics/Mesh.h"
#include <SDL2/SDL.h>
#include "VMEngine/Input.h"

Game& Game::GetGameInstance()
{
	//Create the game only one time, because it's static
	static Game* GameInstance = new Game();
	return *GameInstance;
}

void Game::DestroyGameInstance()
{
	static Game* GameInstance = &GetGameInstance();

	delete GameInstance;
}

void Game::Start(const char* WTitle, bool bFullscreen, int WWidth, int WHeight)
{
	Graphics = make_shared<GraphicsEngine>();

	if (!Graphics->InitGE(WTitle, bFullscreen, WWidth, WHeight))
	{
		bIsGameOver = true;
	}

	Run();
}

Game::Game()
{
	cout << "Game Initialised" << endl;

	Graphics = nullptr;
	bIsGameOver = false;
}

Game::~Game()
{
	//Destroy the graphics from memory with share pointer
	Graphics = nullptr;
	cout << "Game Over..." << endl;
}

void Game::Run()
{
	if (!bIsGameOver)
	{
		GameInput = new Input();

		//create a shader
		ShaderPtr TextureShader = Graphics->CreateShader({
			L"Game/Shaders/TextureShader/TextureShader.svert",
			L"Game/Shaders/TextureShader/TextureShader.sfrag"
			});

		//Created the texture
		TexturePtr TConcrete = Graphics->CreateTexture("Game/Textures/brick_pavement.jpg");
		TexturePtr TGrid = Graphics->CreateTexture("Game/Textures/goldCoins.png");
		TexturePtr TStones = Graphics->CreateTexture("Game/Textures/SquareStones.jpg");
		TexturePtr TBricks = Graphics->CreateTexture("Game/Textures/SquareBrown.jpg");

		//Create the vertex/meshes
		Poly = Graphics->CreateSimpleMeshShape(GeometricShapes::Cube, TextureShader, { TConcrete });
		Cube = Graphics->CreateSimpleMeshShape(GeometricShapes::Polygon, TextureShader, { TGrid });

		//created transformation for the meshes
		Poly->Transform.Location.x = -0.5f;	
		Cube->Transform.Location.x = 1.0f;
	}

	while (!bIsGameOver)
	{
		ProcessInput();

		Update();

		Draw();
	}

	CloseGame();
}

void Game::ProcessInput()
{
	//run the input detection for our game input
	GameInput->ProcessInput();
}

void Game::Update()
{
	//set delta time first always
	static double LastFrameTime = 0.0;
	//set current time since the game has passed
	double CurrentFrameTime = static_cast<double>(SDL_GetTicks64());
	//find the time difference between the last and current frame
	double NewDeltaTime = CurrentFrameTime - LastFrameTime;
	//set delta time as seconds
	DeltaTime = NewDeltaTime / 1000.0;
	//update the last frame time for the next update
	LastFrameTime = CurrentFrameTime;

	Poly->Transform.Rotation.z += 25.0f * GetFDeltaTime();
	Poly->Transform.Rotation.x += 25.0f * GetFDeltaTime();
	Poly->Transform.Rotation.y += 25.0f * GetFDeltaTime();

	Cube->Transform.Rotation.z += -25.0f * GetFDeltaTime();
	Cube->Transform.Rotation.x += -25.0f * GetFDeltaTime();
	Cube->Transform.Rotation.y += -25.0f * GetFDeltaTime();

	Vector3 CameraInput = Vector3(0.0f);

	//move camera forward
	if (GameInput->IsKeyDown(SDL_SCANCODE_W))
		CameraInput.z = 1.0f;
	//move camera backward
	if (GameInput->IsKeyDown(SDL_SCANCODE_S))
		CameraInput.z = -1.0f;
	//move camera left
	if (GameInput->IsKeyDown(SDL_SCANCODE_A))
		CameraInput.x = 1.0f;
	//move camera right
	if (GameInput->IsKeyDown(SDL_SCANCODE_D))
		CameraInput.x = -1.0f;
	//move camera up
	if (GameInput->IsKeyDown(SDL_SCANCODE_Q))
		CameraInput.y = -1.0f;
	//move camera down
	if (GameInput->IsKeyDown(SDL_SCANCODE_E))
		CameraInput.y = 1.0f;

	CameraInput *= 2.0f * GetFDeltaTime();

	Graphics->EngineDefaultCam += CameraInput;
}

void Game::Draw()
{
	Graphics->Draw();
}

void Game::CloseGame()
{
	delete GameInput;
}