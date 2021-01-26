/*************************************************************************
    > File Name: config.h
    > Author: Jintao Yang
    > Mail: 18608842770@163.com 
    > Created Time: 2021年01月26日 星期二 15时46分33秒
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

#ifndef __CONFIG_H__
#define __CONFIG_H__

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

//window defination
const int SCREEN_WIDTH = 200;
const int SCREEN_HEIGHT = 220;

SDL_Color BG_COLOR = {0xa7, 0xba, 0x56, 0xff};
SDL_Color DEEP_COLOR = {0x25, 0x25, 0x26, 0xff};
SDL_Color LIGHT_COLOR = {0x8e, 0x9f, 0x45, 0xff};

#endif

