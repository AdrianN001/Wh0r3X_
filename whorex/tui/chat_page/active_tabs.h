#pragma once
#include <curses.h>
#include <pthread.h> 
#include "whorex/user.h"

/* Size of the popup window  */
#define ACTIVE_TAB_BOX_WINDOW_WIDTH 30
#define ACTIVE_TAB_BOX_WINDOW_HEIGHT 27
/* Placement of the popup window */
#define ACTIVE_TAB_BOX_WINDOW_ROW 87
#define ACTIVE_TAB_BOX_WINDOW_COLS 440


void update_tabs_box(WINDOW* tabs_window, struct user* session_user);
WINDOW* start_tabs_box(WINDOW* base_window);
