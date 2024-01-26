#pragma once
#include <curses.h>
#include <pthread.h> 

/* Size of the popup window  */
#define USERS_BOX_WINDOW_WIDTH 60
#define USERS_BOX_WINDOW_HEIGHT 45
/* Placement of the popup window */
#define USERS_BOX_WINDOW_ROW 70
#define USERS_BOX_WINDOW_COLS 410

typedef struct {
    WINDOW* users_window; 
    char** users_buffer;
    int* users_buffer_size; 
    pthread_mutex_t* users_buffer_mutex;
} users_worker_args;

void* users_box_worker(users_worker_args* args);
WINDOW* start_users_box(WINDOW* base_window, char** users_buffer, int* users_buffer_size, pthread_mutex_t* user_buffer_mutex);
