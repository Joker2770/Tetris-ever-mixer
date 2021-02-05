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
#include "config.h"

#ifdef _win
#include <windows.h>
#else
#include <unistd.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
				SDL_Color bgColor,
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

int main(int argc, char *argv[])
{
    srand((unsigned)time(NULL));

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
			//Clear screen
			SDL_SetRenderDrawColor(gRenderer, BG_COLOR.r, BG_COLOR.g, BG_COLOR.b, BG_COLOR.a);
			SDL_RenderClear(gRenderer);

			//Render quad
			SDL_Rect outline_rect = {5, 5, 110, 210};
			SDL_SetRenderDrawColor(gRenderer, DEEP_COLOR.r, DEEP_COLOR.g, DEEP_COLOR.b, DEEP_COLOR.a);
			SDL_RenderDrawRect(gRenderer, &outline_rect);

			//Render game area
			for (int i = 1; i <= 20; i++)
			{
				for (int j = 1; j <= 10; j++)
				{
					render_rect(j * 10, i * 10, false);
				}
			}

			render_font(gRenderer, gFont, "SCORE", DEEP_COLOR, BG_COLOR, 125, 5, NULL, 0.0, NULL, SDL_FLIP_NONE);
			render_font(gRenderer, gFont, "LINES", DEEP_COLOR, BG_COLOR, 125, 40, NULL, 0.0, NULL, SDL_FLIP_NONE);
			render_font(gRenderer, gFont, "LEVEL", DEEP_COLOR, BG_COLOR, 125, 75, NULL, 0.0, NULL, SDL_FLIP_NONE);
			render_font(gRenderer, gFont, "NEXT", DEEP_COLOR, BG_COLOR, 125, 110, NULL, 0.0, NULL, SDL_FLIP_NONE);

			render_font(gRenderer, gFont, "        0", DEEP_COLOR, LIGHT_COLOR, 145, 20, NULL, 0.0, NULL, SDL_FLIP_NONE);
			render_font(gRenderer, gFont, "        0", DEEP_COLOR, LIGHT_COLOR, 145, 55, NULL, 0.0, NULL, SDL_FLIP_NONE);
			render_font(gRenderer, gFont, "  0", DEEP_COLOR, LIGHT_COLOR, 175, 90, NULL, 0.0, NULL, SDL_FLIP_NONE);

			//Render next area
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					render_rect(135 + j * 10, 125 + i * 10, false);
				}
			}

			shape_data_t gShape;
			p_shape_data_t shape_data = &gShape;
			int i_mode = 0;
			unsigned int i_lines = 0;
			u_int16_t i_seed = 0;
			init_game(0, shape_data);

			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//While application is running
			while (!quit)
			{
				int i_offset = 0;

				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					else if (e.type == SDL_KEYDOWN)
					{
						switch (e.key.keysym.sym)
						{
						case SDLK_UP:
							if (i_seed > 65534)
							{
								i_seed = 0;
							}
							i_seed++;
							//If crash 'left' 'right' or 'down'
							if (!check_collision(shape_data, 1) && !check_collision(shape_data, 2) && !check_collision(shape_data, 2))
								rotate_rock(i_mode, i_seed, shape_data);
							else
								i_seed--;
							break;
						case SDLK_DOWN:
							i_offset = 3;
							break;
						case SDLK_LEFT:
							i_offset = 2;
							break;
						case SDLK_RIGHT:
							i_offset = 1;
							break;
						case SDLK_q:
							quit = true;
							break;
						default:
							break;
						}
					}
				}

				if (i_offset == 2)
				{
					if (!check_collision(shape_data, i_offset))
						shape_data->x--;
				}
				else if (i_offset == 1)
				{
					if (!check_collision(shape_data, i_offset))
						shape_data->x++;
				}
				else if (i_offset == 3)
				{
					while (!check_collision(shape_data, 3))
						shape_data->y++;
				}

				render_rock(135, 125, shape_data->next_bit, true);
				render_rock(shape_data->x*10, shape_data->y*10, shape_data->cur_bit, true);
				SDL_RenderPresent(gRenderer);
				#ifdef _win
				Sleep(1000);
				#else
				usleep(1000000);
				#endif
				render_rock(shape_data->x*10, shape_data->y*10, shape_data->cur_bit, false);
				SDL_RenderPresent(gRenderer);

				if (check_collision(shape_data, 3))
				{
					fix_rock(shape_data);

					//Clear game area
					for (int i = 1; i <= 20; i++)
					{
						for (int j = 1; j <= 10; j++)
						{
							if (GMPOOL[j][i] == 1)
							{
								render_rect(j * 10, i * 10, false);
							}
						}
					}
					SDL_RenderPresent(gRenderer);

					//earsing
					uint16_t i_count = check_erasing();

					//Render game area
					for (int i = 1; i <= 20; i++)
					{
						for (int j = 1; j <= 10; j++)
						{
							if (GMPOOL[j][i] == 1)
							{
								render_rect(j * 10, i * 10, true);
							}
						}
					}
					SDL_RenderPresent(gRenderer);

					if (i_count > 0)
					{
						i_lines += i_count;
						char sTmp[16] = "";
						memset(sTmp, 0, sizeof(sTmp));
						if (i_lines < 10)
						{
							sprintf(sTmp, "        %d", i_lines);
						}
						else if (i_lines < 100)
						{
							sprintf(sTmp, "      %d", i_lines);
						}
						else if (i_lines < 1000)
						{
							sprintf(sTmp, "    %d", i_lines);
						}
						render_font(gRenderer, gFont, sTmp, DEEP_COLOR, LIGHT_COLOR, 145, 55, NULL, 0.0, NULL, SDL_FLIP_NONE);
						SDL_RenderPresent(gRenderer);
					}

					render_rock(135, 125, shape_data->next_bit, false);
					SDL_RenderPresent(gRenderer);
					
					//init rotation
					i_seed = 0;
					shape_data->cur_shape_line = shape_data->next_shape_line;
					shape_data->cur_bit = shape_data->next_bit;
					shape_data->next_shape_line = rand()%7;
					if (i_mode == 0)
						shape_data->next_bit = SRS[shape_data->next_shape_line][0];
					else
						shape_data->next_bit = TGM[shape_data->next_shape_line][0];
					shape_data->x = 4;
					shape_data->y = 1;
					if (check_collision(shape_data, 3))
					{
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

							i_lines = 0;
							render_font(gRenderer, gFont, "Game Over!", LIGHT_COLOR, DEEP_COLOR, 25, 100, NULL, 0.0, NULL, SDL_FLIP_NONE);
							SDL_RenderPresent(gRenderer);
						}
					}
				}
				else
					shape_data->y++;
			}
			SDL_RenderClear(gRenderer);
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
		gWindow = SDL_CreateWindow("Tetris-ever", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
		SDL_SetRenderDrawColor(gRenderer, DEEP_COLOR.r, DEEP_COLOR.g, DEEP_COLOR.b, DEEP_COLOR.a);
	else
		SDL_SetRenderDrawColor(gRenderer, LIGHT_COLOR.r, LIGHT_COLOR.g, LIGHT_COLOR.b, LIGHT_COLOR.a);
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
				SDL_Color bgColor,
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

		//The actual hardware texture
		SDL_Texture* texture = NULL;

		//Create texture from surface pixels
		texture = SDL_CreateTextureFromSurface(sRenderer, textSurface);
		if (texture == NULL)
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
			
			SDL_SetRenderDrawColor(sRenderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
			SDL_RenderFillRect(sRenderer, &renderQuad);

			//Render to screen
			SDL_RenderCopyEx(sRenderer, texture, clip, &renderQuad, angle, center, flip);

			//Free texture
			SDL_DestroyTexture(texture);
			texture = NULL;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
		textSurface = NULL;
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

