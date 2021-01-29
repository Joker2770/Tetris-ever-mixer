/*************************************************************************
    > File Name: tetris.c
    > Author: Jintao Yang
    > Mail: 18608842770@163.com 
    > Created Time: 2021年01月16日 星期六 16时15分24秒
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
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void init_game(int i_mode)
{
    srand((unsigned)time(NULL));

    for (int X = 0; X < 12; X++)
    {
        for (int Y = 0; Y < 22; Y++)
        {
            if (X == 0 || Y == 0 || X == 11 || Y == 21)
                GMPOOL[X][Y] = 1;
            else
                GMPOOL[X][Y] = 0;
        }
    }
}

uint16_t rotate_rock(int i_mode , int i_seed, p_shape_data_t shapeData)
{
    return i_mode == 0 ? SRS[shapeData->cur_shape_line][i_seed&3] : TGM[shapeData->cur_shape_line][i_seed&3];
}

bool check_collision(p_shape_data_t shapeData, int offset)
{
    int pos[4][4] = {
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0},
    };
	int P[4] = {0, 0, 0, 0};
	for(int j=0;j<4;j++)
	{
		P[j] = shapeData->cur_bit&0xF, shapeData->cur_bit>>=4;
        pos[P[j]>>2][P[j]&0x3] = 1;
	}
    
    //check left
    if (offset & 0x3 == 0x2)
    {
        for (int i = 0; i < 4; i++)
        {
            if (GMPOOL[shapeData->x - 1][shapeData->y + i]&pos[0][i] == 1)
                return true;
        }
    }
    //check down
    else if (offset & 0x3 == 0x3)
    {
        for (int i = 0; i < 4; i++)
        {
            if (GMPOOL[shapeData->x + i][shapeData->y + 4]&pos[i][3] == 1)
                return true;
        }
    }
    //check right
    else if (offset & 0x3 == 0x1)
    {
        for (int i = 0; i < 4; i++)
        {
            if (GMPOOL[shapeData->x + 4][shapeData->y + i]&pos[3][i] == 1)
                return true;
        }
    }
    else
    {
        return false;
    }
}