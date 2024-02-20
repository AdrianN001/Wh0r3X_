#pragma once
#include <ncurses.h>
#include <pthread.h>

#include "../../complex_buffer.h"

/* Size of the popup window  */
#define HISTORY_BOX_WINDOW_WIDTH 175
#define HISTORY_BOX_WINDOW_HEIGHT 52
/* Placement of the popup window */
#define HISTORY_BOX_WINDOW_ROW 52
#define HISTORY_BOX_WINDOW_COLS 175

void fetch_current_date(char* buffer);
void fetch_current_time(char* buffer);

void update_history_box(WINDOW* window, char* title, complex_buffer_t* buffer, pthread_mutex_t* gui_mutex);
WINDOW* start_history_box_window(WINDOW* base_window);