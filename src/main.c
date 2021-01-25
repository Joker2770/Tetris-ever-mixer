/*************************************************************************
    > File Name: main.c
    > Author: Jintao Yang
    > Mail: 18608842770@163.com 
    > Created Time: 2021年01月16日 星期六 16时14分40秒
 ************************************************************************/

/* MIT License

Copyright (c) 2021 Joker2770

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE. */

#include "tetris.h"

#ifdef _MSC_VER
//Windows
#include "SDL.h"
#include "SDL_ttf.h"
#else
//Linux...
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#endif

#include <stdio.h>

//window defination
const int SCREEN_WIDTH = 200;
const int SCREEN_HEIGHT = 220;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Render rectangle
void render_rect(int x, int y, bool isDeep);

//Render rock
void render_rock(int x, int y, uint16_t CAC, bool isDeep);

//Render font
void render_font(SDL_Renderer* sRenderer,
				TTF_Font* font,
				const char* textureText,
				SDL_Color textColor,
				int x,
				int y,
				SDL_Rect* clip,
				double angle,
				SDL_Point* center,
				SDL_RendererFlip flip
				);

//Frees media and shuts down SDL
void closeAll();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Font
TTF_Font *gFont = NULL;

//The actual hardware texture
SDL_Texture* gTexture;

int main(int argc, char *argv[])
{
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//While application is running
			while (!quit)
			{
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
				}

				//Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xa7, 0xba, 0x56, 0xff);
				SDL_RenderClear(gRenderer);

				//Render red filled quad
				SDL_Rect outline_rect = {5, 5, 110, 210};
				SDL_SetRenderDrawColor(gRenderer, 0x25, 0x25, 0x26, 0xff);
				SDL_RenderDrawRect(gRenderer, &outline_rect);

				//Render game area
				for (int i = 0; i < 20; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						render_rect((j + 1) * 10, (i + 1) * 10, false);
					}
				}

				SDL_Color color = {0x25, 0x25, 0x26, 0xff};
				render_font(gRenderer, gFont, "SCORE", color, 125, 5, NULL, 0.0, NULL, SDL_FLIP_NONE);
				render_font(gRenderer, gFont, "LINES", color, 125, 40, NULL, 0.0, NULL, SDL_FLIP_NONE);
				render_font(gRenderer, gFont, "LEVEL", color, 125, 75, NULL, 0.0, NULL, SDL_FLIP_NONE);
				render_font(gRenderer, gFont, "NEXT", color, 125, 110, NULL, 0.0, NULL, SDL_FLIP_NONE);

				SDL_Color color_b = {0x8e, 0x9f, 0x45, 0xff};
				render_font(gRenderer, gFont, "888888", color_b, 145, 20, NULL, 0.0, NULL, SDL_FLIP_NONE);
				render_font(gRenderer, gFont, "888888", color_b, 145, 55, NULL, 0.0, NULL, SDL_FLIP_NONE);
				render_font(gRenderer, gFont, "88", color_b, 175, 90, NULL, 0.0, NULL, SDL_FLIP_NONE);

				//Render next area
				for (int i = 0; i < 4; i++)
				{
					for (int j = 0; j < 4; j++)
					{
						render_rect(135 + j * 10, 125 + i * 10, false);
					}
				}

				SDL_RenderPresent(gRenderer);
				SDL_RenderClear(gRenderer);
			}
		}
	}
	closeAll();

	return 0;
}

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("Hello World", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_SOFTWARE);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize SDL_ttf
				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
				}
			}

		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	gFont = TTF_OpenFont("bb3273.ttf", 12);
	if (gFont == NULL)
	{
		printf("Failed to load TTF font: %s\n", TTF_GetError());
	}

	//Nothing to load
	return success;
}

void render_rect(int x, int y, bool isDeep)
{
	//Render filled quad
	SDL_Rect outline_rect = {x + 1 , y + 1, 8, 8};
	SDL_Rect fill_rect = {x + 3, y + 3, 4, 4};
	if (isDeep)
		SDL_SetRenderDrawColor(gRenderer, 0x25, 0x25, 0x26, 0xff);
	else
		SDL_SetRenderDrawColor(gRenderer, 0x8e, 0x9f, 0x45, 0xff);
	SDL_RenderDrawRect(gRenderer, &outline_rect);
	SDL_RenderFillRect(gRenderer, &fill_rect);
}

void render_rock(int x, int y, uint16_t CAC, bool isDeep)
{
	int P[4] = {0, 0, 0, 0};
	for(int j=0;j<=3;j++)
	{
		P[j] = CAC&0xF, CAC>>=4;
		render_rect((P[j]>>2) * 10 + x, (P[j]&0x3) * 10 + y, isDeep);
	}
}

void render_font(SDL_Renderer* sRenderer,
				TTF_Font* font,
				const char* textureText,
				SDL_Color textColor,
				int x,
				int y,
				SDL_Rect* clip,
				double angle,
				SDL_Point* center,
				SDL_RendererFlip flip
				)
{
	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText, textColor);
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		//Create texture from surface pixels
		gTexture = SDL_CreateTextureFromSurface(sRenderer, textSurface);
		if (gTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Set rendering space and render to screen
			SDL_Rect renderQuad = { x, y, textSurface->w, textSurface->h};

			//Set clip rendering dimensions
			if (clip != NULL)
			{
				renderQuad.w = clip->w;
				renderQuad.h = clip->h;
			}

			//Render to screen
			SDL_RenderCopyEx(sRenderer, gTexture, clip, &renderQuad, angle, center, flip);
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}
}

void closeAll()
{
	//Free global font
	if (NULL != gFont)
	{
		TTF_CloseFont(gFont);
		gFont = NULL;
	}

	//Free texture if it exists
	if (gTexture != NULL)
	{
		SDL_DestroyTexture(gTexture);
		gTexture = NULL;
	}

	//Destroy window
	if (NULL != gRenderer)
	{
		SDL_DestroyRenderer(gRenderer);
		gRenderer = NULL;
	}
	if (NULL != gWindow)
	{
		SDL_DestroyWindow(gWindow);
		gWindow = NULL;
	}

	//Quit SDL subsystems
	TTF_Quit();
	SDL_Quit();
}

