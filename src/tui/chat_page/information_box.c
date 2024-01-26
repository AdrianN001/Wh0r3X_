#pragma once
#include "../../../lib/tui/chat_page.h"
#include <pthread.h>


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


void* information_box_worker(info_box_worker_args* args){

    WINDOW* info_box_window = args->info_box_window;
    const char* server_name = args->server_name;

    char time_buffer[20] = {0}; 
    char date_buffer[25] = {0};

    for (;;){
        fetch_current_time(time_buffer);
        mvwaddstr(info_box_window, 1,1, time_buffer);
        fetch_current_date(date_buffer);
        mvwaddstr(info_box_window, INFORMATION_BOX_WINDOW_HEIGHT -2, INFORMATION_BOX_WINDOW_WIDTH - 10, date_buffer);

        refresh();
        wrefresh(info_box_window);
        sleep(1);
    }

}



WINDOW* start_information_box(WINDOW* base_window, const char* server_name){
    WINDOW* popup_window;
    pthread_t worker_thread; 


    const int x_center = (INFORMATION_BOX_WINDOW_COLS - INFORMATION_BOX_WINDOW_WIDTH) / 2;
    const int y_center = (INFORMATION_BOX_WINDOW_ROW - INFORMATION_BOX_WINDOW_HEIGHT) / 2;

    if( ( popup_window = subwin(base_window, INFORMATION_BOX_WINDOW_HEIGHT, INFORMATION_BOX_WINDOW_WIDTH, y_center, x_center) ) == NULL ){

        return 0; // unnecesesy box, it doesn't have to exit from the whole program
    } 


    keypad(popup_window, TRUE);
    box(popup_window, 0, 0);
    mvwaddstr(popup_window, 0, INFORMATION_BOX_WINDOW_WIDTH / 2 - 5, "About You:" );
    mvwaddstr(popup_window, INFORMATION_BOX_WINDOW_HEIGHT / 2, INFORMATION_BOX_WINDOW_WIDTH / 2 - (strlen(server_name) / 2), server_name );

    info_box_worker_args args = {0};
    args.info_box_window = popup_window; 
    args.server_name = server_name;

    pthread_create(&worker_thread, NULL, information_box_worker, (void*)&args);
    // POTENTIAL RACE CONDITION!
    /*
        If the stack gets cleared before the thread can start
        then it will have an invalid pointer &args, which is no bueno  
    */
    refresh();

    return popup_window;
}