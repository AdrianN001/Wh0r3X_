#pragma once
#include "chat_page/input_field.h"
#include "chat_page/information_box.h"
#include "chat_page/users_box.h"
#include "chat_page/history.h"
#include "color_pairs.h"
#include <unistd.h>
#include <curses.h>

#ifndef assert(x)
#define assert(x) if((!(x))){printf("assertion error!\n error at %s() function\n",__func__); exit(1);}
#endif

/* History Box */
void start_history_box(WINDOW* base_window);
