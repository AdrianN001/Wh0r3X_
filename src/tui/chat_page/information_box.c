#include "../../../lib/tui/chat_page.h"
#include <pthread.h>


void fetch_current_time(char* buffer){
    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    sprintf(buffer, " %02d:%02d:%02d ", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
}
    

void fetch_current_date(char* buffer){
    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    sprintf(buffer, "%d-%02d-%02d",timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday);
}




void update_info_box(WINDOW* info_window){

    char date_buffer[32] = {0};
    char time_buffer[32] = {0};

    fetch_current_time(time_buffer);
    mvwaddstr(info_window, 1,1, time_buffer);
    fetch_current_date(date_buffer);
    mvwaddstr(info_window, INFORMATION_BOX_WINDOW_HEIGHT -2, INFORMATION_BOX_WINDOW_WIDTH - 10, date_buffer);

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