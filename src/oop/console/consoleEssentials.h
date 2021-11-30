#pragma once
#include <iostream>
#include <time.h>
#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#define sleep(ms) Sleep(ms)
#endif

#ifdef __unix__
#include <unistd.h> // for sleep()
#endif

const unsigned char BLACK = 219;

/* type of each pixel */
typedef struct
{
    unsigned char elem;
    unsigned char color;
} PIXELDATA;

BOOL gotoxy(const WORD x, const WORD y)
{
    COORD xy;
    xy.X = x;
    xy.Y = y;
    return SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy);
}

void hideCursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

/* print the screen to console */
inline void printScreen(int width, int height, PIXELDATA **screen)
{
    gotoxy(0, 0); // top-left corner
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            PIXELDATA *cur = &screen[i][j];
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), cur->color);
            printf("%c", cur->elem); // may be faster than cout
        }
    }
}

/* initialize the screen to element se */
inline void initScreen(int width, int height, PIXELDATA **screen, PIXELDATA se)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            screen[i][j] = se;
        }
    }
}

/* draw a rectangle to (x, y), size (szx, szy) */
inline void putRectangle(int x, int y, int szx, int szy, int color, PIXELDATA **screen)
{
    for (int i = y; i < y + szy; i++)
    {
        for (int j = x; j < x + szx; j++)
        {
            screen[i][j].color = color;
        }
    }
}