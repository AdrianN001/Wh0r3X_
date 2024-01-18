#pragma once
#include <ncurses.h>

#define MAIN_COLOR_PAIR             1
#define MAIN_COLOR_PAIR_REVERSED    2
#define WARNING_COLOR_PAIR          3
#define WARNING_COLOR_PAIR_REVERSED 4
#define ERROR_COLOR_PAIR            5
#define ERROR_COLOR_PAIR_REVERSED   6

void define_colors(){
    /*  Base colors */
    init_pair(MAIN_COLOR_PAIR, COLOR_BLACK, COLOR_WHITE);
    init_pair(MAIN_COLOR_PAIR_REVERSED, COLOR_WHITE, COLOR_BLACK);

    /* Warning colors */
    init_pair(WARNING_COLOR_PAIR, COLOR_YELLOW, COLOR_BLACK);
    init_pair(WARNING_COLOR_PAIR_REVERSED, COLOR_BLACK, COLOR_YELLOW);

    /* Error colors */
    init_pair(ERROR_COLOR_PAIR, COLOR_RED, COLOR_BLACK);
    init_pair(ERROR_COLOR_PAIR_REVERSED, COLOR_BLACK, COLOR_RED);
}