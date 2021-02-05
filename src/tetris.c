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

void init_game(int i_mode, p_shape_data_t shapeData)
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

    shapeData->x = 4;
    shapeData->y = 1;
    shapeData->cur_shape_line = rand()%7;
    shapeData->next_shape_line = rand()%7;
    if (i_mode == 1)
    {
        shapeData->cur_bit = SRS[shapeData->cur_shape_line][rand()%4];
        shapeData->next_bit = SRS[shapeData->next_shape_line][rand()%4];
    }
    else
    {
        shapeData->cur_bit = TGM[shapeData->cur_shape_line][rand()%4];
        shapeData->next_bit = TGM[shapeData->next_shape_line][rand()%4];
    }
}

uint16_t rotate_rock(int i_mode , uint16_t i_seed, p_shape_data_t shapeData)
{
    if (i_mode == 1)
        shapeData->cur_bit = SRS[shapeData->cur_shape_line][i_seed&3];
    else
        shapeData->cur_bit = TGM[shapeData->cur_shape_line][i_seed&3];
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
    uint16_t u16_tmp_bit = shapeData->cur_bit;
	for(int j=0;j<4;j++)
	{
		P[j] = u16_tmp_bit&0xF, u16_tmp_bit>>=4;
        pos[P[j]>>2][P[j]&0x3] = 1;
	}

    //check left
    if ((offset & 3) == 2)
    {
        int iFlag = 0;
        for (int x = 3; x >= 0; x--)
        {
            for (int y = 0; y < 4; y++)
            {
                iFlag |= (GMPOOL[shapeData->x + x - 1][shapeData->y + y]) & (pos[x][y]);
                if (iFlag == 1)
                    return true;
            }
        }
    }
    //check down
    else if ((offset & 3) == 3)
    {
        int iFlag = 0;
        for (int x = 0; x < 4; x++)
        {
            for (int y = 0; y < 4; y++)
            {
                iFlag |= (GMPOOL[shapeData->x + x][shapeData->y + y + 1]) & (pos[x][y]);
                if (iFlag == 1)
                    return true;
            }
        }
    }
    //check right
    else if ((offset & 3) == 1)
    {
        int iFlag = 0;
        for (int x = 0; x < 4; x++)
        {
            for (int y = 0; y < 4; y++)
            {
                iFlag |= (GMPOOL[shapeData->x + x + 1][shapeData->y + y]) & (pos[x][y]);
                if (iFlag == 1)
                    return true;
            }
        }
    }
    else
    {
        return false;
    }
    
    return false;
}

uint16_t check_erasing()
{
    uint16_t iCount = 0;
    for (int i = 1; i <= 20; i++)
    {
        int i_flag = 1;
        for (int j = 1; j <= 10; j++)
        {
            i_flag &= GMPOOL[j][i];
        }
        if (i_flag == 1)
        {
            iCount++;
            for (int m = i; m > 1; m--)
            {
                for (int n = 1; n <= 10; n++)
                {
                    GMPOOL[n][m] = GMPOOL[n][m - 1];
                }
            }
        }
    }
    return iCount;
}

void fix_rock(p_shape_data_t shapeData)
{
    int P[4] = {0, 0, 0, 0};
    uint16_t u16_tmp_bit = shapeData->cur_bit;
    for (int i = 0; i < 4; i++)
    {
        P[i] = u16_tmp_bit&0xF, u16_tmp_bit>>=4;
        GMPOOL[shapeData->x + (P[i]>>2)][shapeData->y + (P[i]&0x3)] = 1;
    }
}
