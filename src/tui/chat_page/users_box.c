#pragma once
#include "../../../lib/tui/chat_page.h"
#include <pthread.h>

void* users_box_worker(users_worker_args* args){
    pthread_mutex_t* lock = args->users_buffer_mutex;
    int* buffer_size = args->users_buffer_size;
    char** users_buffer = args->users_buffer;
    WINDOW* users_window = args->users_window;

    for (;;){
        pthread_mutex_lock(lock); 
        const int current_size_of_buffer = *buffer_size;
        for (int i = 0; i < current_size_of_buffer; i++){
            assert(users_window != NULL)
            assert(users_buffer[i]);
            mvwaddstr(users_window, 2 + (i), 2, users_buffer[i]);
        }
        pthread_mutex_unlock(lock);
        wrefresh(users_window);
        sleep(3);
    }
    free(args);

}

WINDOW* start_users_box(WINDOW* base_window, char** users_buffer, int* users_buffer_size, pthread_mutex_t* user_buffer_mutex){
    WINDOW* popup_window;
    pthread_t working_thread; 

    const int x_center = (USERS_BOX_WINDOW_COLS - USERS_BOX_WINDOW_WIDTH) / 2;
    const int y_center = (USERS_BOX_WINDOW_ROW - USERS_BOX_WINDOW_HEIGHT) / 2;

    popup_window = subwin(base_window, USERS_BOX_WINDOW_HEIGHT, USERS_BOX_WINDOW_WIDTH, y_center, x_center);

 
    assert(popup_window != NULL)


    keypad(popup_window, TRUE);
    box(popup_window, 0,0);
    mvwaddstr(popup_window, 0, USERS_BOX_WINDOW_WIDTH / 2 - 5, " Users: " );

    users_worker_args args = {0};
    args.users_window = popup_window;
    args.users_buffer = users_buffer;
    args.users_buffer_size = users_buffer_size;
    args.users_buffer_mutex = user_buffer_mutex;

    
    pthread_create(&working_thread, NULL, users_box_worker, (void*)&args);
    // POTENTIAL RACE CONDITION!
    /*
        If the stack gets cleared before the thread can start
        then it will have an invalid pointer &args, which is no bueno  
    */

    refresh();

    return popup_window;
}