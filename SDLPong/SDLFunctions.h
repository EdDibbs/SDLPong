#include <iostream>
#include <SDL.h>


void logSDLError(std::ostream &os, const std::string &msg)
{
	os << msg.c_str() << " Error: " << SDL_GetError() << std::endl;
}

SDL_Texture* loadTexture(const std::string &file, SDL_Renderer* ren)
{
	SDL_Texture *texture = NULL;
	//load the texture
	SDL_Surface *bmp = SDL_LoadBMP(file.c_str());
	//make sure the texture loaded correctly
	if (bmp != nullptr)
	{
		texture = SDL_CreateTextureFromSurface(ren, bmp);
		SDL_FreeSurface(bmp);
		if (texture == nullptr)
		{
			logSDLError(std::cout, "SDL_CreateTextureFromSurfaceError: ");
		}

	}
	else
	{
		logSDLError(std::cout, "SDL_Surface");
	}

	return texture;
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y)
{
	//Setup the destination rectangle to be at the position we want
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	//Query the texture to get its width and height to use
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopy(ren, tex, NULL, &dst);
}