#pragma once
#include "chat_page/information_box.h"
#include <curses.h>

/* History Box */
void start_history_box(WINDOW* base_window);


/* Users Box */
void start_users_box(WINDOW* base_window);

/* Input Field Box */
void start_input_field_box(WINDOW* base_window);