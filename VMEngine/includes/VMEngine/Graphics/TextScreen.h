#pragma once

struct SDL_Texture;
struct SDL_Surface;
struct SDL_Color;
struct SDL_Renderer;
struct SDL_Rect;

class TextScreen
{
public:
	TextScreen(const char* FontFilePath, const char* String, SDL_Color* Color, int DefaultSize = 24);
	~TextScreen();
	void draw();

private:
	SDL_Surface* FontSurface;
	SDL_Texture* FontTexture;
	SDL_Renderer* Renderer;

	SDL_Rect* FontInfo;
};