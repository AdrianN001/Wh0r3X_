#ifndef TIME_C
#define TIME_C

#include <time.h>
#include "whorex/time.h"
#include <stdlib.h>
#include <stdio.h>


int fetch_current_time(char* buffer){
    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    return sprintf(buffer, " %02d:%02d:%02d ", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
}
    

int fetch_current_date(char* buffer){
    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    return sprintf(buffer, "%d-%02d-%02d",timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday);
}

int fetch_current_time_h_m(char* buffer){
    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    return sprintf(buffer, "%02d:%02d", timeinfo->tm_hour, timeinfo->tm_min);
}
#endif