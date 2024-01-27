#include "../../../lib/tui/chat_page.h"

void update_history_box(WINDOW* window, char** buffer, int size_of_buffer, pthread_mutex_t* gui_mutex){
    pthread_mutex_lock(gui_mutex);


    for (int i = size_of_buffer -1 ; i>=0; i--){
        mvwaddstr(window, 1 + i, 1, buffer[i]);
    }

    pthread_mutex_unlock(gui_mutex);
}

WINDOW* start_history_box_window(WINDOW* base_window){
    WINDOW* popup_window;


    const int x_center = (HISTORY_BOX_WINDOW_COLS - HISTORY_BOX_WINDOW_WIDTH) / 2;
    const int y_center = (HISTORY_BOX_WINDOW_ROW - HISTORY_BOX_WINDOW_HEIGHT) / 2;

    popup_window = subwin(base_window, HISTORY_BOX_WINDOW_HEIGHT, HISTORY_BOX_WINDOW_WIDTH, y_center, x_center);
    assert(popup_window != NULL)



    keypad(popup_window, TRUE);
    box(popup_window, 0, 0);

    refresh();
    wrefresh(popup_window);
    return popup_window;
}