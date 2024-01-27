#pragma once
#include "form_buffer.h"
#include <ncurses.h>
#include <curses.h>

/* Size of the popup window  */
#define POPUP_WINDOW_WIDTH 75
#define POPUP_WINDOW_HEIGHT 20
/* Placement of the popup window */
#define POPUP_WINDOW_ROW 48
#define POPUP_WINDOW_COLS 220

/* Login form state */
#define USERNAME_FORM 0
#define NICKNAME_FORM 1
#define REALNAME_FORM 2

/* Form position vertically */
#define USERNAME_FORM_POSITION 4
#define NICKNAME_FORM_POSITION 6
#define REALNAME_FORM_POSITION 8

typedef struct login_result{
    char* username;
    char* nickname;
    char* realname;
} login_result_t;

void print_background(WINDOW* window);
void set_cursor(WINDOW* window, short buffer_id, form_buffer_t* buffers);
login_result_t start_login_page(WINDOW* main_window);
void print_login_result(login_result_t* res);
void free_login_result(login_result_t* res);