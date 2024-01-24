#pragma once

#include "color_pairs.h"
#include "form_buffer.h"
#include <ncurses.h>
#include <curses.h>

/* Size of the popup window  */
#define CONNECTION_POPUP_WINDOW_WIDTH 75
#define CONNECTION_POPUP_WINDOW_HEIGHT 20
/* Placement of the popup window */
#define CONNECTION_POPUP_WINDOW_ROW 48
#define CONNECTION_POPUP_WINDOW_COLS 220


void print_border(WINDOW* popup_window);
// returns the server name
char* start_connection_popup_box(WINDOW* base_window);

typedef struct {
    char** data;
    size_t size;
} connection_history_t;

connection_history_t get_connection_history();
void free_connection_history(connection_history_t* history);