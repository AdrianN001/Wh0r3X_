#pragma once
#include <stdio.h>

//loads the time in format HH-MM-SS into the buffer 
int fetch_current_time(char* buffer);
// loads the date in format YYYY-MM-DD into buffer
int fetch_current_date(char* buffer);
//loads the time in format HH-MM into the buffer 
int fetch_current_time_h_m(char* buffer);  