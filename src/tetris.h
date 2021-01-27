/*************************************************************************
    > File Name: tetris.h
    > Author: Jintao Yang
    > Mail: 18608842770@163.com 
    > Created Time: 2021年01月16日 星期六 16时15分16秒
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

#ifndef __TETRIS_H__
#define __TETRIS_H__

#ifdef _MSC_VER // take care of M$ compiler
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

static const uint16_t SRS[7][4]={
	{0x159D,0x89AB,0x26AE,0x4567},
	{0x0159,0x4856,0x159A,0x4526},
	{0x8159,0x456A,0x1592,0x0456},
	{0x4859,0x4859,0x4859,0x4859},
	{0x4815,0x459A,0x5926,0x0156},
	{0x4159,0x4596,0x1596,0x4156},
	{0x0459,0x8596,0x156A,0x4152}
};

static const uint16_t TGM[7][4]={
	{0x159D,0x89AB,0x159D,0x89AB},
	{0x126A,0x4856,0x159A,0x4526},
	{0x926A,0x456A,0x1592,0x0456},
	{0x4859,0x4859,0x4859,0x4859},
	{0x5926,0x0156,0x5926,0x0156},
	{0x4159,0x4596,0x1596,0x4156},
	{0x156A,0x4152,0x156A,0x4152}
};

static int GMPOOL[12][22] = {};

typedef struct shape_data
{
	uint16_t cur_bit;
	uint16_t next_bit;
	int x;
	int y;
} shape_data_t;

static shape_data_t shapeData;

void init_game(void);
void restart_game(void);
bool check_collision(void);
void rotate_rock(void);
bool check_erasing(void);

#endif
