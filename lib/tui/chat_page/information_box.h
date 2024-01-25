#pragma once



/* Size of the popup window  */
#define INFORMATION_BOX_WINDOW_WIDTH 60
#define INFORMATION_BOX_WINDOW_HEIGHT 15
/* Placement of the popup window */
#define INFORMATION_BOX_WINDOW_ROW 15
#define INFORMATION_BOX_WINDOW_COLS 410

void fetch_current_date(char* buffer);
void fetch_current_time(char* buffer);
void start_information_box(WINDOW* base_window);
