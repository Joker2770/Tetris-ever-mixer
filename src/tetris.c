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

void init_game(void)
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

    shapeData.cur_bit = i_mode == 0 ? SRS[rand()][rand()] : TGM[rand()][rand()];
    shapeData.next_bit = i_mode == 0 ? SRS[rand()][rand()] : TGM[rand()][rand()];
    shapeData.x = 4;
    shapeData.y = 1;
}