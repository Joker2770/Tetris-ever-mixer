/*************************************************************************
    > File Name: tetris.h
    > Author: Jintao Yang
    > Mail: 18608842770@163.com 
    > Created Time: 2021年01月16日 星期六 16时15分16秒
 ************************************************************************/

/* MIT License

Copyright (c) 2021-2023 Joker2770

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

#ifndef __TETRIS_H__
#define __TETRIS_H__

#ifdef _MSC_VER		 // take care of M$ compiler
#if _MSC_VER <= 1200 // below VC6
#error Are you still use VC6?!
#else // up VC6
#if _MSC_VER >= 1600
#include <stdint.h>
#else // below VC10
typedef signed char int8_t;
typedef unsigned short uint16_t;
#endif
#ifndef __cplusplus // for VC
typedef int bool;
#define true 1
#define false 0
#endif
#endif
#else // other compilers
#include <stdint.h>
#ifndef __cplusplus
#include <stdbool.h>
#endif
#endif

typedef struct rock_shape_data
{
	uint16_t cur_bit;
	uint16_t next_bit;
	int cur_shape_line;
	int next_shape_line;
	int x;
	int y;
} shape_data_t, *p_shape_data_t;

void init_game(int, p_shape_data_t);
void restart_game(void);
void fix_rock(p_shape_data_t);
bool check_collision(p_shape_data_t, int);
uint16_t rotate_rock(int, uint16_t, p_shape_data_t);
uint16_t check_erasing(void);

#endif
