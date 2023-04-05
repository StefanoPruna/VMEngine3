#include "VMEngine/Game.h"
#include "VMEngine/Graphics/GraphicsEngine.h"
#include "VMEngine/Graphics/ShaderProgram.h"
#include "VMEngine/Graphics/Texture.h"
#include "VMEngine/Graphics/Model.h"
#include <SDL2/SDL.h>
#include "VMEngine/Input.h"
#include "VMEngine/Graphics/Camera.h"
#include "VMEngine/Graphics/Material.h"

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

TexturePtr Game::GetDefaultEngineTexture()
{
	return Graphics->DefaultEngineTexture;
}

MaterialPtr Game::GetDefaultEngineMaterial()
{
	return Graphics->DefaultEngineMaterial;
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
		//TexturePtr TConcrete = Graphics->CreateTexture("Game/Textures/brick_pavement.jpg");
		TexturePtr TGoldCoins = Graphics->CreateTexture("Game/Textures/goldCoins.png");
		TexturePtr TRedCoins = Graphics->CreateTexture("Game/Textures/goldCoins.png");
		TexturePtr TBackground = Graphics->CreateTexture("Game/Textures/Entrytunnel.jpg");
		//TexturePtr TBricks = Graphics->CreateTexture("Game/Textures/SquareBrown.jpg");

		//create the materials
		//MaterialPtr MConcrete = make_shared<Material>();
		MaterialPtr MGoldCoins = make_shared<Material>();
		MaterialPtr MRedCoins = make_shared<Material>();
		MaterialPtr MBackground = make_shared<Material>();

		MGoldCoins->BaseColour = TGoldCoins;
		MRedCoins->BaseColour = TRedCoins;
		MBackground->BaseColour = TBackground;

		//Create the vertex/meshes
		GoldCoin = Graphics->CreateSimpleModelShape(GeometricShapes::Cube, TextureShader);
		RedCoin = Graphics->CreateSimpleModelShape(GeometricShapes::Cube, TextureShader);
		Background = Graphics->CreateSimpleModelShape(GeometricShapes::Cube, TextureShader);
		//Wall = Graphics->CreateSimpleModelShape(GeometricShapes::Cube, TextureShader);

		//set materials 
		GoldCoin->SetMaterialBySlot(0, MGoldCoins);
		RedCoin->SetMaterialBySlot(0, MRedCoins);
		Background->SetMaterialBySlot(0, MBackground);

		//created transformation for the meshes
		GoldCoin->Transform.Location = Vector3(-1.0f, 0.0f, 1.0f);
		RedCoin->Transform.Location = Vector3(1.0f, 0.0f, -1.0f);
		Background->Transform.Scale = Vector3(10.0f);
		Background->Transform.Location = Vector3(-1.0f, 0.0f, 1.0f);
		
		//import custom meshes
		Wall = Graphics->ImportModel("Game/Models/source/WallDamaged.obj", TextureShader);
		Wall2 = Graphics->ImportModel("Game/Models/source/WallDamaged.obj", TextureShader);
		Wall3 = Graphics->ImportModel("Game/Models/source/sci-fi_wall.obj", TextureShader);
		
		//transform the meshes
		Wall->Transform.Scale = Vector3(0.1f);
		//Wall->Transform.Rotation.z = 90.0f;
		Wall->Transform.Location = Vector3(15.0f, -3.0f, -5.0f);
		Wall2->Transform.Scale = Vector3(0.1f);
		Wall2->Transform.Location = Vector3(15.0f, -3.0f, 7.0f);
		Wall3->Transform.Rotation.x = 90.0f;
		Wall3->Transform.Location = Vector3(10.0f, -3.0f, 0.0f);

		//create the texture
		TexturePtr TWall = Graphics->CreateTexture("Game/Textures/WallDamaged.png");
		TexturePtr TWall2 = Graphics->CreateTexture("Game/Textures/spacescene.jpg");
		TexturePtr TWall3 = Graphics->CreateTexture("Game/Textures/TexturesCom.jpg");

		//create the material
		MaterialPtr MWall = make_shared<Material>();
		MWall->BaseColour = TWall;
		MaterialPtr MWall2 = make_shared<Material>();
		MWall2->BaseColour = TWall2;
		MaterialPtr MWall3 = make_shared<Material>();
		MWall3->BaseColour = TWall3;

		//apply the material
		Wall->SetMaterialBySlot(1, MWall);
		Wall2->SetMaterialBySlot(1, MWall2);
		Wall3->SetMaterialBySlot(1, MWall3);
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

	RedCoin->Transform.Rotation.z += 25.0f * GetFDeltaTime();
	RedCoin->Transform.Rotation.x += 25.0f * GetFDeltaTime();
	RedCoin->Transform.Rotation.y += 25.0f * GetFDeltaTime();

	GoldCoin->Transform.Rotation.z += -25.0f * GetFDeltaTime();
	GoldCoin->Transform.Rotation.x += -25.0f * GetFDeltaTime();
	GoldCoin->Transform.Rotation.y += -25.0f * GetFDeltaTime();

	Vector3 CameraInput = Vector3(0.0f);
	CDirection CamDirections = Graphics->EngineDefaultCam->GetDirections();

	//Moving objects right and left, or up and down
	static int Move = 1.0f;
	//Move up and down
	if (GoldCoin->Transform.Location.y > 2.5f)
		Move = -1.0f;

	if (GoldCoin->Transform.Location.y < -2.5f)
		Move = 1.0f;
	//speed of the object
	GoldCoin->Transform.Location.y += (1.5f * Move) * GetFDeltaTime();

	//right and left
	if (RedCoin->Transform.Location.z > 3.0f)
		Move = -1.0f;

	if (RedCoin->Transform.Location.z < -3.0f)
		Move = 1.0f;
	//speed of the object
	RedCoin->Transform.Location.x += (1.0f * Move) * GetFDeltaTime();

	//move camera forward
	if (GameInput->IsKeyDown(SDL_SCANCODE_W))
		CameraInput += CamDirections.Forward;
	//move camera backward
	if (GameInput->IsKeyDown(SDL_SCANCODE_S))
		CameraInput += -CamDirections.Forward;
	//move camera left
	if (GameInput->IsKeyDown(SDL_SCANCODE_A))
		CameraInput += -CamDirections.Right;
	//move camera right
	if (GameInput->IsKeyDown(SDL_SCANCODE_D))
		CameraInput += CamDirections.Right;
	//move camera up
	if (GameInput->IsKeyDown(SDL_SCANCODE_E))
		CameraInput += CamDirections.Up;
	//move camera down
	if (GameInput->IsKeyDown(SDL_SCANCODE_Q))
		CameraInput += -CamDirections.Up;

	////If the C key is pressed, it should reset the camera to its FOV degrees, 
	////but I cannot make it work
	//if (GameInput->IsKeyDown(SDL_SCANCODE_C))
	//	Graphics->EngineDefaultCam->GetCameraData().FOV;

	/*CameraInput *= 3.0f * GetFDeltaTime();

	Vector3 NewLocation = Graphics->EngineDefaultCam->GetTransforms().Location += CameraInput;
	Graphics->EngineDefaultCam->Translate(NewLocation);*/

	Graphics->EngineDefaultCam->AddMovementInput(CameraInput);

	if (GameInput->IsMouseButtonDown(MouseButtons::RIGHT))
	{
		Graphics->EngineDefaultCam->RotatePitch(-GameInput->MouseYDelta * GetFDeltaTime());
		Graphics->EngineDefaultCam->RotateYaw(GameInput->MouseXDelta * GetFDeltaTime());
		GameInput->ShowCursor(false);
	}
	else
		GameInput->ShowCursor(true);
		
	////test mouse inputs
	//if (GameInput->IsMouseButtonDown(MouseButtons::MIDDLE))
	//	cout << "middle mouse button down" << endl;
	//else
	//	cout << "middle mouse button up" << endl;
}

void Game::Draw()
{
	Graphics->Draw();
}

void Game::CloseGame()
{
	delete GameInput;
}