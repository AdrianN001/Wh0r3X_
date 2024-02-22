#include "../../../lib/tui/chat_page.h"
#include "../../format.c"
#include "../../complex_buffer.c"
#include "../../../lib/tui/color_pairs.h"

void update_history_box(WINDOW* window, char* title, complex_buffer_t* buffer, pthread_mutex_t* gui_mutex){


    /* Clear the window  */
    for( int y = 0; y < 50; y++){
        wmove(window, y, 0);          // move to begining of line
        wclrtoeol(window);          // clear line
    }
    // clrtoeol clears the border 
    box(window, 0, 0);

    mvwaddstr(window, 0, 110, title);

    if (buffer->size  == buffer->max_size){
        // The buffer's full and therefore it will circleate
        int index = buffer->starting_point + 1;
        int y_offset = 0;

        while (index != buffer->starting_point ){
            mvwaddstr(window, 1 + y_offset, 2, buffer->buffer[index]);

            y_offset++;
            index = index == (buffer->max_size) ? 0 : (index + 1) ;
        }
        
    }else{
        for (int i = buffer->size -1 ; i>=0; i--){
            mvwaddstr(window, 1+i, 2, buffer->buffer[i]);
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