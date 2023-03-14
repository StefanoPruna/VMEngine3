#include "VMEngine/Graphics/GraphicsEngine.h"
#include "GLEW/glew.h"
#include "VMEngine/Graphics/VertexArrayObject.h"
#include "VMEngine/CoreMinimal.h"
#include "VMEngine/Graphics/Mesh.h"
#include "VMEngine/Graphics/ShaderProgram.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "VMEngine/Graphics/Texture.h"

GraphicsEngine::GraphicsEngine()
{
	SdlWindow = nullptr;
	SdlGLContext = NULL;
	bWireFrameMode = false;
	EngineDefaultCam = Vector3(0.0f, 0.0f, -2.0f);
}

GraphicsEngine::~GraphicsEngine()
{
	//clear from the memory
	MeshStack.clear();
	Shader = nullptr;
	//remove textures from the memory
	TextureStack.clear();

	//Delete the SDL window from memory
	SDL_DestroyWindow(SdlWindow);
	//destroy the GL 
	SDL_GL_DeleteContext(SdlGLContext);
	//close the SDL framework
	SDL_Quit();

	cout << "Destroy the Graphic Engine..." << "\n";
}

bool GraphicsEngine::InitGE(const char* WTitle, bool bFullscreen, int WWidth, int WHeight)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		cout << "SDL failed: " << SDL_GetError() << "\n";
		return false;
	}

	//Use OpenGL 4.6 compatibility and set default
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);

	//Set the fullscreen
	int FullscreenFlag = 0;

	if (bFullscreen)
	{
		FullscreenFlag = SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN;
	}
	else
	{
		FullscreenFlag = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;
	}

	//Create the SDL2 window
	SdlWindow = SDL_CreateWindow(
		WTitle,
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WWidth, WHeight,
		FullscreenFlag
	);

	if (SdlWindow == nullptr)
	{
		cout << "SDL window failed: " << SDL_GetError() << endl;
		return false;
	}

	//add the GL attributes to the window
	SdlGLContext = SDL_GL_CreateContext(SdlWindow);

	if (SdlGLContext == NULL)
	{
		cout << "SDL GL context failed: " << SDL_GetError() << "\n";
		return false;
	}

	//To make 
	glewExperimental = GL_TRUE;

	const GLenum InitGLEW = glewInit();

	if (InitGLEW != GLEW_OK)
	{
		cout << "GLEW failed: " << glewGetErrorString(InitGLEW) << endl;
		return false;
	}

	glEnable(GL_DEPTH_TEST);

	return true;
}

void GraphicsEngine::PresentGraphics()
{
	//Present the new graphics using OpenGL
	SDL_GL_SwapWindow(SdlWindow);
}

void GraphicsEngine::ClearGraphics()
{
	//R G B A for background
	glClearColor(0.23f, 0.38f, 0.47f, 1.0f);

	//Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GraphicsEngine::Draw()
{
	ClearGraphics();

	HandleWireFrameMode(false);

	//run through each mesh and call its draw method
	for (MeshPtr LMesh : MeshStack)
	{
		LMesh->Draw();
	}

	PresentGraphics();
}

SDL_Window* GraphicsEngine::GetWindow() const
{
	return SdlWindow;
}

MeshPtr GraphicsEngine::CreateSimpleMeshShape(GeometricShapes Shape, ShaderPtr MeshShader, TexturePtrStack MeshTextures)
{
	//Initialise a new mesh class
	MeshPtr NewMesh = make_shared<Mesh>();

	//make sure that it works
	if (!NewMesh->CreateSimpleShape(Shape, MeshShader, MeshTextures))
		return nullptr;


	//add mesh into the stack of meshes to be rendered
	MeshStack.push_back(NewMesh);

	//return the new mesh
	return NewMesh;
}

ShaderPtr GraphicsEngine::CreateShader(VFShaderParams ShaderFilePaths)
{
	ShaderPtr NewShader = make_shared<ShaderProgram>();

	NewShader->InitVFShader(ShaderFilePaths);

	//add the shader to our graphics engine
	Shader = NewShader;

	return NewShader;
}

TexturePtr GraphicsEngine::CreateTexture(const char* FilePath)
{
	TexturePtr NewTexture = nullptr;

	// run through all the textures and check if one with the same path exists
	for (TexturePtr TestTexture : TextureStack)
	{
		if (TestTexture->GetFilePath() == FilePath)
		{
			//pass in the already created texture
			NewTexture = TestTexture;
			cout << "Texture found! Assigning current texture" << endl;
			break;
		}
	}

	//if there isn't texture already in existance
	if (NewTexture == nullptr)
	{
		cout << "Creating a new texture" << endl;
		NewTexture = make_shared<Texture>();

		if (NewTexture->CreateTextureFromFilePath(FilePath))
		{
			cout << "Texture " << NewTexture->GetID() << "creation success" << endl;

			//add the texture to the texture stack
			TextureStack.push_back(NewTexture);
		}
	}

	return NewTexture;
}

void GraphicsEngine::ApplyScreenTransformations(ShaderPtr Shader)
{
	//the angle of the camera planes / zoom
	float FOV = 70.0f;
	//view position
	Vector3 ViewPosition = EngineDefaultCam;
	//find the size of the screen and calculate the aspect ratio
	int WWidth, WHeight = 0;
	//use SDL to get the size of the window
	SDL_GetWindowSize(SdlWindow, &WWidth, &WHeight);
	//calculate the aspect ration from the window size
	//we use static_cast<float> because W
	float AR = static_cast<float>(WWidth) / static_cast<float>(max(WHeight, 1));

	//create the default coordinates for the projection and view
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	//update the coordinates for 3D
	view = glm::translate(view, ViewPosition);
	//create the perspective view to allow us to see in 3D
	//and adjusting the newar and far clip for the 3D view
	projection = glm::perspective(glm::radians(FOV), AR, 0.01f, 1000.0f);

	Shader->SetMat4("view", view);
	Shader->SetMat4("projection", projection);
}

void GraphicsEngine::HandleWireFrameMode(bool bShowWireFrameMode)
{
	//if wireframe mode is set, change it and viceversa
	if (bShowWireFrameMode != bWireFrameMode)
	{
		//change how OpenGL renders between the vertices
		bWireFrameMode = bShowWireFrameMode;
		if (bWireFrameMode)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		cout << "WireFrame mode updated..." << endl;
	}
}
