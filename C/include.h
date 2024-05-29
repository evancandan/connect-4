#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <stdbool.h>
#include <time.h>

#define GRID_HEIGHT 6
#define GRID_WIDTH 7

typedef struct game_s
{
    char grid[GRID_HEIGHT][GRID_WIDTH];
    bool player;
    int cursor;
    int key;
    int player1;
    int player2;
    bool pause;

} game_t;