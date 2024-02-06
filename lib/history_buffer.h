#pragma once

#define MAX_MESSAGE_LENGTH 1024

typedef struct history_buffer{
    char** buffer;
    int size;
    int max_size;
} history_buffer_t;

history_buffer_t create_history_buffer(const int max_size);
void append_to_history_buffer(history_buffer_t* buffer_obj, char* new_buffer);
void append_to_history_buffer_with_size(history_buffer_t* buffer_obj, char* new_buffer, size_t n);
void pop_from_history_buffer(history_buffer_t* buffer_obj);
void free_history_buffer(history_buffer_t* buffer);

void print_history_buffer(history_buffer_t* buffer);