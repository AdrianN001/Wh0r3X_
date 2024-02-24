#pragma once
#include <curses.h>



/* Size of the popup window  */
#define INFORMATION_BOX_WINDOW_WIDTH 60
#define INFORMATION_BOX_WINDOW_HEIGHT 10
/* Placement of the popup window */
#define INFORMATION_BOX_WINDOW_ROW 10
#define INFORMATION_BOX_WINDOW_COLS 410

void update_info_box(WINDOW* info_window, char* nickname);
WINDOW* start_information_box(WINDOW* base_window, const char* server_name);