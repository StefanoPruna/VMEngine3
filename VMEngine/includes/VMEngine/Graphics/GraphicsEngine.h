#pragma once
#include "VMEngine/CoreMinimal.h"
#include "SDL2//SDL.h"
#include "VMEngine/Math/Transformations.h"

class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();

	//Initialised Graphic Engine/ the Window
	bool InitGE(const char* WTitle, bool bFullscreen, int WWidth, int WHeight);

	//Show the newest frame graphic
	void PresentGraphics();
	//Clear the old frame
	void ClearGraphics();

	//Handle the rendering of our graphics
	//Return the sdl window
	void Draw();

	SDL_Window* GetWindow() const;

	//Add a new 
	MeshPtr CreateSimpleMeshShape(GeometricShapes Shape, ShaderPtr MeshShader, MaterialPtr MeshMaterial);

	ShaderPtr CreateShader(VFShaderParams ShaderFilePahts);

	//create a texture and add it to the tyexture stack
	//avoid duplicates
	TexturePtr CreateTexture(const char* FilePath);

	//create the 3D space for the model to relate itself to screen and camera coordinates
	void ApplyScreenTransformations(ShaderPtr Shader);

	//default camera
	CameraPtr EngineDefaultCam;

	//default texture
	TexturePtr DefaultEngineTexture;
private:
	SDL_Window* SdlWindow;

	SDL_GLContext SdlGLContext;
	
	//Handle wireframe mode
	void HandleWireFrameMode(bool bShowWireFrameMode);
	//set wireframe
	bool bWireFrameMode;

	//single shader
	ShaderPtr Shader;
	//store a vector of textures
	TexturePtrStack TextureStack;

	MeshPtrStack MeshStack;
};