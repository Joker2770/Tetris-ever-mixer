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

#ifdef _WIN32
//Windows
#include "SDL.h"
#else
//Linux...
#include <SDL2/SDL.h>
#endif

#include <stdio.h>

//window defination
const int SCREEN_WIDTH = 240;
const int SCREEN_HEIGHT = 220;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Render rectangle
void render_rect(int x, int y, bool isDeep);

//Render rock
void render_rock(int x, int y, uint16_t CAC);

//Frees media and shuts down SDL
void closeAll();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

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
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
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
				
				//Update screen
				SDL_RenderPresent(gRenderer);
			}

		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

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

void render_rock(int x, int y, uint16_t CAC)
{
	int P[4] = {0, 0, 0, 0};
	for(int j=0;j<=3;j++)
	{
		P[j] = CAC&0xF, CAC>>=4;
		render_rect((P[j]>>2) * 10 + x, (P[j]&0x3) * 10 + y, true);
	}
}

void closeAll()
{
	//Destroy window    
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

