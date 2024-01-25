#include "../../lib/tui/chat_page.h"
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>


/* Information Box */

void fetch_current_time(char* buffer){
    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    if (timeinfo->tm_sec >= 10){
        sprintf(buffer, "%d:%d:%d", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
    }else{
        sprintf(buffer, "%d:%d:0%d", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

    }
}

void fetch_current_date(char* buffer){
    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    sprintf(buffer, "%d-%d-%d",timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday);
}



void start_information_box(WINDOW* base_window){
    WINDOW* popup_window;
    char time_buffer[20] = {0}; 
    char date_buffer[25] = {0};


    const int x_center = (INFORMATION_BOX_WINDOW_COLS - INFORMATION_BOX_WINDOW_WIDTH) / 2;
    const int y_center = (INFORMATION_BOX_WINDOW_ROW - INFORMATION_BOX_WINDOW_HEIGHT) / 2;

    if( ( popup_window = subwin(base_window, INFORMATION_BOX_WINDOW_HEIGHT, INFORMATION_BOX_WINDOW_WIDTH, y_center, x_center) ) == NULL ){

        return; // unnecesesy box, it doesn't have to exit from the whole program
    } 


    keypad(popup_window, TRUE);
    box(popup_window, 0, 0);
    mvwaddstr(popup_window, 0, INFORMATION_BOX_WINDOW_WIDTH / 2 - 5, "About You:" );
    mvwaddstr(popup_window, INFORMATION_BOX_WINDOW_HEIGHT / 2, INFORMATION_BOX_WINDOW_WIDTH / 2 - 10, "Not yet implemented!" );


    for (;;){
        fetch_current_time(time_buffer);
        mvwaddstr(popup_window, 1,1, time_buffer);
        fetch_current_date(date_buffer);
        mvwaddstr(popup_window, INFORMATION_BOX_WINDOW_HEIGHT -2, INFORMATION_BOX_WINDOW_WIDTH - 10, date_buffer);

        refresh();
        wrefresh(popup_window);
        sleep(1);
    }



    for(;;){}

    delwin(popup_window);
    endwin();
    refresh();


}