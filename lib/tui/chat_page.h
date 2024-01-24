#pragma once
#include <curses.h>

/* History Box */
void start_history_box(WINDOW* base_window);

/* Information Box */
void fetch_current_date(char* buffer);
void fetch_current_time(char* buffer);
void start_information_box(WINDOW* base_window);


/* Users Box */
void start_users_box(WINDOW* base_window);

/* Input Field Box */
void start_input_field_box(WINDOW* base_window);