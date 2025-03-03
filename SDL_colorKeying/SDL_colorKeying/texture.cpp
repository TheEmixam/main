#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "texture.h"
#include "base.h"

TGfxTexture::TGfxTexture()
{
	//Initialize
	m_pTexture = nullptr;
	m_iWidth = 0;
	m_iHeight = 0;
}
TGfxTexture::~TGfxTexture()
{
	//Deallocate
	free();
}

bool TGfxTexture::loadFromFile(std::string path)
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = nullptr;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == nullptr)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(g_pRenderer, loadedSurface);
		if (newTexture == nullptr)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//Get image dimensions
			m_iWidth = loadedSurface->w;
			m_iHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	m_pTexture = newTexture;
	return m_pTexture != nullptr;
}

void TGfxTexture::free()
{
	//Free texture if it exists
	if (m_pTexture != nullptr)
	{
		SDL_DestroyTexture(m_pTexture);
		m_pTexture = nullptr;
		m_iWidth = 0;
		m_iHeight = 0;
	}
}

void TGfxTexture::render(int x, int y)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, m_iWidth, m_iHeight };

	SDL_RenderCopy(g_pRenderer, m_pTexture, nullptr, &renderQuad);
}


void TGfxTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	//Modulate texture
	SDL_SetTextureColorMod(m_pTexture, red, green, blue);
}
void TGfxTexture::setBlendMode(SDL_BlendMode blending)
{
	//Set blending function
	SDL_SetTextureBlendMode(m_pTexture, blending);
}

void TGfxTexture::setAlpha(Uint8 alpha)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(m_pTexture, alpha);
}