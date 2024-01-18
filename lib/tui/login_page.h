#pragma once
#include <ncurses.h>

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

typedef struct login_result{
    char username[24];
    char nicknake[24];
    char realname[24];
} login_result_t;

void print_background(WINDOW* window);
login_result_t start_login_page();