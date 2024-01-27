#pragma once
#include <curses.h>



/* Size of the popup window  */
#define INPUT_FIELD_BOX_WINDOW_WIDTH 170
#define INPUT_FIELD_BOX_WINDOW_HEIGHT 5
/* Placement of the popup window */
#define INPUT_FIELD_BOX_WINDOW_ROW 110
#define INPUT_FIELD_BOX_WINDOW_COLS 170


void update_input_box(WINDOW* window, char new_character, form_buffer_t* buffer);

WINDOW* start_input_field_box(WINDOW* base_window);
