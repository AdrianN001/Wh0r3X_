#pragma once
#include <curses.h>
#include <pthread.h> 

/* Size of the popup window  */
#define USERS_BOX_WINDOW_WIDTH 30
#define USERS_BOX_WINDOW_HEIGHT 47
/* Placement of the popup window */
#define USERS_BOX_WINDOW_ROW 67
#define USERS_BOX_WINDOW_COLS 380

typedef struct {
    WINDOW* users_window; 
    char** users_buffer;
    int* users_buffer_size; 
    pthread_mutex_t* users_buffer_mutex;
    pthread_mutex_t* gui_mutex;
} users_worker_args;

void update_users_box(WINDOW* users_window, char** buffer, int* size_of_users, pthread_mutex_t* gui_lock);
WINDOW* start_users_box(WINDOW* base_window, char** users_buffer, int* users_buffer_size, pthread_mutex_t* user_buffer_mutex);
