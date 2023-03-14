#pragma once
#include "VMEngine/CoreMinimal.h"

//Hold the image data for conversion to the texture file
struct ImportImageData
{
	int w = 0;
	int h = 0;
	int channels = 0;
};

class Texture
{
public:
	Texture();
	~Texture();

	//create texture file from imported image path
	bool CreateTextureFromFilePath(const char* FilePath);

	//return the OpenGL txture ID
	vmuint GetID() const { return TextureID; }

	//bind the texture as the current texture in OpenGL
	void BindTexture();

	//assigns the relevant data to the current loaded texture; turn the texture on
	void ActivateTexture(vmuint Index);

	//clear the texture in OpenGL
	static void ResetTexture();

	//return the file path
	const char* GetFilePath() const { return FilePath; }

private:
	//hold the ID for the texture in OpenGL
	vmuint TextureID;
	//hold the filepth to avoid duplicates
	const char* FilePath;
};