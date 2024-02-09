#include "../../../lib/tui/chat_page.h"





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