#pragma once
#include <curses.h>



/* Size of the popup window  */
#define INFORMATION_BOX_WINDOW_WIDTH 60
#define INFORMATION_BOX_WINDOW_HEIGHT 10
/* Placement of the popup window */
#define INFORMATION_BOX_WINDOW_ROW 10
#define INFORMATION_BOX_WINDOW_COLS 410

void fetch_current_date(char* buffer);
void fetch_current_time(char* buffer);



typedef struct {
    WINDOW* info_box_window; 
    const char* server_name;
} info_box_worker_args;

void* information_box_worker(info_box_worker_args* args);

WINDOW* start_information_box(WINDOW* base_window, const char* server_name);
