#pragma once

#include <curses.h>

#define MAIN_COLOR_PAIR             1
#define MAIN_COLOR_PAIR_REVERSED    2
#define WARNING_COLOR_PAIR          3
#define WARNING_COLOR_PAIR_REVERSED 4
#define ERROR_COLOR_PAIR            5
#define ERROR_COLOR_PAIR_REVERSED   6

#define PROMPT_INPUT_TEXT           7

#define LOGIN_PAGE_START            10


void initialize_color_pairs();