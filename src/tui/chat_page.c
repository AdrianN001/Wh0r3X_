#include "../../lib/tui/chat_page.h"
#include <stdio.h>
#include <time.h>
#include <unistd.h>


/* Information Box */

void fetch_current_time(char* buffer){
    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    sprintf(buffer, "%d:%d:%d", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
}

void fetch_current_date(char* buffer){
    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    sprintf(buffer, "%d-%d-%d",timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday);
}

void start_information_box(WINDOW* base_window){

    WINDOW* popup_window = subwin(base_window, 40, 75, 82, 14);


    keypad(popup_window, TRUE);
    box(popup_window, 0, 0);
    mvwaddstr(popup_window, 10, 2, "Connection:" );

    refresh();
    wrefresh(popup_window);

    for(;;){}

    delwin(popup_window);
    endwin();
    refresh();


}