#include "whorex/tui.h"
#include "whorex/time.h"
#include <pthread.h>





void update_info_box(WINDOW* info_window, char* nickname){

    char date_buffer[32] = {0};
    char time_buffer[32] = {0};

    (void)fetch_current_time(time_buffer);
    mvwaddstr(info_window, 1,1, time_buffer);
    (void)fetch_current_date(date_buffer);
    mvwaddstr(info_window, INFORMATION_BOX_WINDOW_HEIGHT -2, INFORMATION_BOX_WINDOW_WIDTH - 12, date_buffer);

    mvwaddstr(info_window, INFORMATION_BOX_WINDOW_HEIGHT/ 2 + 2, INFORMATION_BOX_WINDOW_WIDTH/ 2 - (strlen(nickname) / 2), nickname);

    wrefresh(info_window);
}



WINDOW* start_information_box(WINDOW* base_window, const char* server_name){
    WINDOW* popup_window;


    const int x_center = (INFORMATION_BOX_WINDOW_COLS - INFORMATION_BOX_WINDOW_WIDTH) / 2;
    const int y_center = (INFORMATION_BOX_WINDOW_ROW - INFORMATION_BOX_WINDOW_HEIGHT) / 2;

    popup_window = subwin(base_window, INFORMATION_BOX_WINDOW_HEIGHT, INFORMATION_BOX_WINDOW_WIDTH, y_center, x_center);
    assert(popup_window != NULL)



    keypad(popup_window, TRUE);
    box(popup_window, 0, 0);
    mvwaddstr(popup_window, 0, INFORMATION_BOX_WINDOW_WIDTH / 2 - 5, "About You:" );
    mvwaddstr(popup_window, INFORMATION_BOX_WINDOW_HEIGHT / 2, INFORMATION_BOX_WINDOW_WIDTH / 2 - (strlen(server_name) / 2), server_name );

    refresh();
    wrefresh(popup_window);
    return popup_window;
}