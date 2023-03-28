#include "VMEngine/Graphics/Material.h"
#include "VMEngine/Graphics/Texture.h"
#include "VMEngine/Game.h"
#include "VMEngine/Graphics/ShaderProgram.h"

Material::Material()
{
	if (Game::GetGameInstance().GetDefaultEngineTexture() != nullptr)
		BaseColour = Game::GetGameInstance().GetDefaultEngineTexture();
	else
		BaseColour = nullptr;
}

Material::~Material()
{
	BaseColour = nullptr;
}

void Material::Draw(ShaderPtr Shader)
{
	if (BaseColour != nullptr)
	{
		//activate the texture for slot 0
		BaseColour->ActivateTexture(0);
		//telling the shader to get the texture colour from slot 0
		Shader->SetInt("TextureColour", 0);
		//bind the texture to OpenGL
		BaseColour->BindTexture();
	}
}
