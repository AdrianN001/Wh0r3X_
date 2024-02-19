#include "../../../lib/tui/chat_page.h"



void update_tabs_box(WINDOW* tabs_window, struct user* session_user){


    

    for( int y = 2; y < 12; y++){
        wmove(tabs_window, y, 1);          // move to begining of line
        wclrtoeol(tabs_window);          // clear line
    }
    // clrtoeol clears the border and the title
    box(tabs_window, 0, 0);
    mvwaddstr(tabs_window, 0, ACTIVE_TAB_BOX_WINDOW_WIDTH / 2 - 5, "Active Tabs:" );


    int offset = 0;
    for( tab_t* current_tab_to_print = session_user->list_of_active_channels_head;
        current_tab_to_print != NULL; 
        current_tab_to_print = current_tab_to_print->next ){
        if(current_tab_to_print == session_user->current_channel){
            attron(COLOR_PAIR(WARNING_COLOR_PAIR));
        }
        mvwaddstr(tabs_window, offset + 2, 2, current_tab_to_print->name);
        if(current_tab_to_print == session_user->current_channel){
            attroff(COLOR_PAIR(WARNING_COLOR_PAIR));
        }
        wrefresh(tabs_window);
        offset++;
    }

    refresh();
    wrefresh(tabs_window);
}


WINDOW* start_tabs_box(WINDOW* base_window){
    WINDOW* popup_window;


    const int x_center = (ACTIVE_TAB_BOX_WINDOW_COLS - ACTIVE_TAB_BOX_WINDOW_WIDTH) / 2;
    const int y_center = (ACTIVE_TAB_BOX_WINDOW_ROW - ACTIVE_TAB_BOX_WINDOW_HEIGHT) / 2;

    popup_window = subwin(base_window, ACTIVE_TAB_BOX_WINDOW_HEIGHT, ACTIVE_TAB_BOX_WINDOW_WIDTH, y_center, x_center);
    assert(popup_window != NULL)



    keypad(popup_window, TRUE);
    box(popup_window, 0, 0);
    mvwaddstr(popup_window, 0, ACTIVE_TAB_BOX_WINDOW_WIDTH / 2 - 5, "Active Tabs:" );
    refresh();
    wrefresh(popup_window);
    return popup_window;
}