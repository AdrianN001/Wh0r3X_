#include "whorex/tui.h"
#include <pthread.h>
#include <stdlib.h>


void update_users_box(WINDOW* users_window, char** users_buffer, int* size_of_users, pthread_mutex_t* gui_lock){
    
    pthread_mutex_lock(gui_lock);

    const int current_size_of_buffer = *size_of_users;
    for (int i = 0; i < current_size_of_buffer; i++){
        assert(users_window != NULL)
        assert(users_buffer[i]);
        mvwaddstr(users_window, 3 + (i), 3, users_buffer[i]);
    }
    
    pthread_mutex_unlock(gui_lock);

}

WINDOW* start_users_box(WINDOW* base_window, char** users_buffer, int* users_buffer_size, pthread_mutex_t* user_buffer_mutex){
    WINDOW* popup_window;

    const int x_center = (USERS_BOX_WINDOW_COLS - USERS_BOX_WINDOW_WIDTH) / 2;
    const int y_center = (USERS_BOX_WINDOW_ROW - USERS_BOX_WINDOW_HEIGHT) / 2;

    popup_window = subwin(base_window, USERS_BOX_WINDOW_HEIGHT, USERS_BOX_WINDOW_WIDTH, y_center, x_center);

 
    assert(popup_window != NULL)


    keypad(popup_window, TRUE);
    box(popup_window, 0,0);
    mvwaddstr(popup_window, 0, USERS_BOX_WINDOW_WIDTH / 2 - 5, " Users: " );

    refresh();
    wrefresh(popup_window);

    return popup_window;
}