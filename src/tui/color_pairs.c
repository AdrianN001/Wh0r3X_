#include "whorex/tui.h"


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
    init_pair(LOGIN_PAGE_START,9, COLOR_BLACK);         
    init_pair(11, COLOR_YELLOW, COLOR_BLACK);
    init_pair(12, COLOR_GREEN, COLOR_BLACK);
    init_pair(13, COLOR_BLACK, COLOR_BLACK);
    init_pair(14, COLOR_GREEN, COLOR_BLACK);
    init_pair(15, 12, COLOR_BLACK);
}