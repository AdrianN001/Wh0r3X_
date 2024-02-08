#include "../../../lib/tui/chat_page.h"
#include "../../complex_buffer.c"
#include "../../../lib/tui/color_pairs.h"

void update_history_box(WINDOW* window, complex_buffer_t* buffer, pthread_mutex_t* gui_mutex){

    bool is_header_active = false;
    for (int i = buffer->size -1 ; i>=0; i--){
        for(int character_index = 0; character_index< strlen(buffer->buffer[i]); character_index++){
            if(buffer->buffer[i][character_index] == ':'){
                is_header_active = !is_header_active;
            }

            if(is_header_active){
                wattron(window, COLOR_PAIR(MAIN_COLOR_PAIR_REVERSED));
                mvwaddch(window, 1 + i, 2+character_index, buffer->buffer[i][character_index]);
                wattroff(window, COLOR_PAIR(MAIN_COLOR_PAIR_REVERSED));

            }else{
                mvwaddch(window, 1 + i, 2+character_index, buffer->buffer[i][character_index]);
            }
        }
    }
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