#include "VMEngine/Graphics/TextScreen.h"
#include "SDL2/SDL_ttf.h"
#include "VMEngine/Game.h"
#include "VMEngine/Graphics/GraphicsEngine.h"

TextScreen::TextScreen(const char* FontFilePath, const char* String, SDL_Color Color = { 225 }, int DefaultSize)
{
	//install font
	TTF_Font* Font = TTF_OpenFont(FontFilePath, DefaultSize);

	FontSurface = TTF_RenderText_Solid(Font, String, *Colour);

	Renderer = Game::GetGameInstance().GetGraphicsEngine()->UIRenderer;

	FontTexture = SDL_CreateTextureFromSurface(Renderer, FontSurface);

	FontInfo->x = 0;
	FontInfo->y = y;
	FontInfo->w = FontSurface->w;
	FontInfo->h = FontSurface->h;
}

TextScreen::~TextScreen()
{
	SDL_DestroyTexture(FontTexture);
	SDL_FreeSurface(FontSurface);
}

void TextScreen::draw()
{
	SDL_RenderCopy(Renderer, FontTexture)
}