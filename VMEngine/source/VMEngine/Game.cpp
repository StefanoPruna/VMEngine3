#include "VMEngine/Game.h"
#include "VMEngine/Graphics/GraphicsEngine.h"
#include "VMEngine/Graphics/ShaderProgram.h"
#include "VMEngine/Graphics/Texture.h"
#include "VMEngine/Graphics/Model.h"
#include <SDL2/SDL.h>
#include "VMEngine/Input.h"
#include "VMEngine/Graphics/Camera.h"
#include "VMEngine/Graphics/Material.h"
#include "VMEngine/Collisions/Collision.h"
#include "VMEngine/Graphics/TextScreen.h"

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

void Game::RemoveModelFromGame(ModelPtr& ModelToRemove)
{
	//remove from the graphics engine
	Graphics->RemoveModel(ModelToRemove);

	//change the reference to nullptr and remove from the game
	ModelToRemove = nullptr;
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
		
		//import custom meshes for environment
		Wall = Graphics->ImportModel("Game/Models/source/WallDamaged.obj", TextureShader);//Wall on the left
		Wall2 = Graphics->ImportModel("Game/Models/source/WallDamaged.obj", TextureShader);//Wall on the Right
		Wall3 = Graphics->ImportModel("Game/Models/source/sci_fi_wall2.obj", TextureShader);//Bottom part
		Background = Graphics->ImportModel("Game/Models/source/sci_fi_wall.obj", TextureShader);//Divider
		Wall4 = Graphics->ImportModel("Game/Models/source/WallDamaged.obj", TextureShader);//Wall on the Left
		Wall5 = Graphics->ImportModel("Game/Models/source/WallDamaged.obj", TextureShader);//Wall on the Right

		//for collectables
		GoldCoin = Graphics->ImportModel("Game/Models/Primitives/Sphere.fbx", TextureShader);//Gold Sphere
		RedCoin = Graphics->ImportModel("Game/Models/Primitives/Cube.fbx", TextureShader);//Red Cube
		
		//Add Collision box to the objects
		GoldCoin->AddCollisionToModel(Vector3(1.9f), Vector3(0.0f, 0.0f, 0.0f));
		RedCoin->AddCollisionToModel(Vector3(1.3f));

		//transform the meshes
		Wall->Transform.Scale = Vector3(0.2f);
		Wall->Transform.Location = Vector3(15.0f, -3.0f, -12.0f);
		Wall2->Transform.Scale = Vector3(0.2f);
		Wall2->Transform.Location = Vector3(15.0f, -3.0f, 15.0f);		
		Wall3->Transform.Scale = Vector3(6.0f);
		Wall3->Transform.Rotation.x = 90.0f;
		Wall3->Transform.Location = Vector3(38.0f, 0.0f, -8.0f);
		Background->Transform.Scale = Vector3(5.0f);
		Background->Transform.Location = Vector3(38.0f, -12.0f, 0.0f);
		Background->Transform.Rotation.y = 45.0f;
		Wall4->Transform.Location = Vector3(45.0f, -8.0f, -24.0f);
		Wall4->Transform.Scale = Vector3(0.2f);
		Wall4->Transform.Rotation.y = 45.0f;
		Wall5->Transform.Location = Vector3(47.0f, -8.0f, 26.0f);
		Wall5->Transform.Scale = Vector3(0.2f);
		Wall5->Transform.Rotation.y = -45.0f;

		//Collectables
		GoldCoin->Transform.Location = Vector3(3.0f, 0.0f, 1.0f);
		RedCoin->Transform.Location = Vector3(1.0f, 0.0f, -1.0f);

		//create the texture
		TexturePtr TWall = Graphics->CreateTexture("Game/Textures/Background2.jpg");
		TexturePtr TWall2 = Graphics->CreateTexture("Game/Textures/Background2.jpg");
		TexturePtr TWall3 = Graphics->CreateTexture("Game/Textures/TexturesCom.jpg");
		TexturePtr TWall4 = Graphics->CreateTexture("Game/Textures/Entrytunnel.jpg");
		TexturePtr TWall5 = Graphics->CreateTexture("Game/Textures/Entrytunnel.jpg");

		TexturePtr TGoldCoins = Graphics->CreateTexture("Game/Textures/goldCoins.png");
		TexturePtr TRedCoins = Graphics->CreateTexture("Game/Textures/goldCoins.png");
		TexturePtr TBackground = Graphics->CreateTexture("Game/Textures/text4.jpg");

		//create the material
		MaterialPtr MWall = make_shared<Material>();
		MWall->BaseColour.TextureV3 = TWall;
		MaterialPtr MWall2 = make_shared<Material>();
		MWall2->BaseColour.TextureV3 = TWall2;
		MaterialPtr MWall3 = make_shared<Material>();
		MWall3->BaseColour.TextureV3 = TWall3;
		MaterialPtr MWall4 = make_shared<Material>();
		MWall4->BaseColour.TextureV3 = TWall4;
		MaterialPtr MWall5 = make_shared<Material>();
		MWall5->BaseColour.TextureV3 = TWall5;

		//create the materials
		MaterialPtr MGoldCoins = make_shared<Material>();
		MaterialPtr MRedCoins = make_shared<Material>();
		MaterialPtr MBackground = make_shared<Material>();
		MGoldCoins->BaseColour.TextureV3 = TGoldCoins;
		MRedCoins->BaseColour.TextureV3 = TRedCoins;
		MBackground->BaseColour.TextureV3 = TBackground;

		//apply the material
		Wall->SetMaterialBySlot(1, MWall);
		Wall2->SetMaterialBySlot(1, MWall2);
		Wall3->SetMaterialBySlot(1, MWall3);
		Wall4->SetMaterialBySlot(1, MWall4);
		Wall5->SetMaterialBySlot(1, MWall5);

		//set materials 
		GoldCoin->SetMaterialBySlot(0, MGoldCoins);
		RedCoin->SetMaterialBySlot(0, MRedCoins);
		Background->SetMaterialBySlot(0, MBackground);

		//Assign Yellow light
		GoldCoin->GetMaterialBySlot(0)->EmissiveColour.MultiplierV3 = Vector3(0.1f, 0.1f, 0.0f);
		//Assign Red light
		RedCoin->GetMaterialBySlot(0)->EmissiveColour.MultiplierV3 = Vector3(2.0f, 0.0f, 0.0f);
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

	Vector3 CameraInput = Vector3(0.0f);
	CDirection CamDirections = Graphics->EngineDefaultCam->GetDirections();

	//Moving objects right and left, or up and down
	static int Move = 1.0f;

	if (GoldCoin != nullptr)
	{
		//Move up and down
		if (GoldCoin->Transform.Location.y > 2.5f)
			Move = -1.0f;

		if (GoldCoin->Transform.Location.y < -2.5f)
			Move = 1.0f;
		//speed of the object
		GoldCoin->Transform.Location.y += (1.5f * Move) * GetFDeltaTime();
	}

	if (RedCoin != nullptr)
	{
		//right and left
		if (RedCoin->Transform.Location.z > 3.0f)
			Move = -1.0f;

		if (RedCoin->Transform.Location.z < -3.0f)
			Move = 1.0f;
		//speed of the object
		RedCoin->Transform.Location.x += (1.0f * Move) * GetFDeltaTime();
	}
	

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

	Graphics->EngineDefaultCam->AddMovementInput(CameraInput);

	if (GameInput->IsMouseButtonDown(MouseButtons::RIGHT))
	{
		Graphics->EngineDefaultCam->RotatePitch(-GameInput->MouseYDelta);
		Graphics->EngineDefaultCam->RotateYaw(GameInput->MouseXDelta);
		GameInput->ShowCursor(false);
	}
	else
		GameInput->ShowCursor(true);
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

	if (RedCoin != nullptr)
	{
		RedCoin->Transform.Rotation.z += 25.0f * GetFDeltaTime();
		RedCoin->Transform.Rotation.x += 25.0f * GetFDeltaTime();
		RedCoin->Transform.Rotation.y += 25.0f * GetFDeltaTime();
	}

	if (GoldCoin != nullptr)
	{
		GoldCoin->Transform.Rotation.z += -25.0f * GetFDeltaTime();
		GoldCoin->Transform.Rotation.x += -25.0f * GetFDeltaTime();
		GoldCoin->Transform.Rotation.y += -25.0f * GetFDeltaTime();
	}
		
	Graphics->EngineDefaultCam->Update();

	//do collision stuff
	CollisionPtr CamCol = Graphics->EngineDefaultCam->GetCameraCollision();

	//if the camera runs into the coin, the coin will be removed
	if (GoldCoin != nullptr && CamCol->IsOverlapping(*GoldCoin->GetCollision()))
		RemoveModelFromGame(GoldCoin);

	if (RedCoin != nullptr && CamCol->IsOverlapping(*RedCoin->GetCollision()))
		RemoveModelFromGame(RedCoin);
}

void Game::Draw()
{
	Graphics->ClearGraphics();

	Graphics->Draw();

	/*TextScreen* scoreText = new TextScreen(20, "Game/Textures/arial.ttf", 600, 20);
	scoreText->draw();*/

	//debug draw the camera collision
	CollisionPtr CamCol = Graphics->EngineDefaultCam->GetCameraCollision();

	if (GoldCoin != nullptr && CamCol->IsOverlapping(*GoldCoin->GetCollision()))
		CamCol->DebugDraw(Vector3(0.0f, 255.0f, 0.0f));
	else
		CamCol->DebugDraw(Vector3(255.0f, 0.0f, 0.0f));

	if (RedCoin != nullptr && CamCol->IsOverlapping(*RedCoin->GetCollision()))
		CamCol->DebugDraw(Vector3(0.0f, 255.0f, 0.0f));
	else
		CamCol->DebugDraw(Vector3(255.0f, 0.0f, 0.0f));

	Graphics->PresentGraphics();
}

void Game::CloseGame()
{
	delete GameInput;
}