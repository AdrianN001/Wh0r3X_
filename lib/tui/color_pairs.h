#pragma once
#include <curses.h>

#define MAIN_COLOR_PAIR             1
#define MAIN_COLOR_PAIR_REVERSED    2
#define WARNING_COLOR_PAIR          3
#define WARNING_COLOR_PAIR_REVERSED 4
#define ERROR_COLOR_PAIR            5
#define ERROR_COLOR_PAIR_REVERSED   6

#define PROMPT_INPUT_TEXT           7

#define LOGIN_PAGE                  10
#define LOGIN_PAGE2                 11
#define LOGIN_PAGE3                 12
#define LOGIN_PAGE4                 13
#define LOGIN_PAGE5                 14



void initialize_color_pairs(){
    /*  Base colors */
    init_pair(MAIN_COLOR_PAIR, COLOR_BLACK, COLOR_WHITE);
    init_pair(MAIN_COLOR_PAIR_REVERSED, COLOR_WHITE, COLOR_BLACK);

    /* Warning colors */
    init_pair(WARNING_COLOR_PAIR, COLOR_YELLOW, COLOR_BLACK);
    init_pair(WARNING_COLOR_PAIR_REVERSED, COLOR_BLACK, COLOR_YELLOW);

    /* Error colors */
    init_pair(ERROR_COLOR_PAIR, COLOR_RED, COLOR_BLACK);
    init_pair(ERROR_COLOR_PAIR_REVERSED, COLOR_BLACK, COLOR_RED);

    /* Prompt color */
    init_pair(PROMPT_INPUT_TEXT, COLOR_BLACK, COLOR_WHITE);

    /* Login Page Colors */
    init_pair(LOGIN_PAGE, 8, COLOR_BLACK);          // grey->black
    init_pair(LOGIN_PAGE2, COLOR_WHITE, COLOR_BLACK);
    init_pair(LOGIN_PAGE3, COLOR_RED, COLOR_BLACK); // dark_blue-> black
    init_pair(LOGIN_PAGE4, 1, COLOR_BLACK); // red->black
    init_pair(LOGIN_PAGE5, COLOR_MAGENTA, COLOR_BLACK); // red->black



}