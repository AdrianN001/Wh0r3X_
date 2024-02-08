#pragma once
#include <stdbool.h> 

#define MAX_MESSAGE_LENGTH 1024

typedef struct complex_buffer{
    char** buffer;
    int size;
    int max_size;
} complex_buffer_t;

void append_to_complex_buffer(complex_buffer_t* buffer_obj, char* new_buffer);
void append_to_complex_buffer_with_line_break(complex_buffer_t* buffer_obj, char* new_buffer);
void append_to_complex_buffer_with_size(complex_buffer_t* buffer_obj, char* new_buffer, size_t n);

// Returns the index
int complex_buffer_contains(complex_buffer_t* buffer, char* searched_buffer);

int remove_from_complex_buffer(complex_buffer_t* buffer, char* removed_buffer);

void pop_from_complex_buffer(complex_buffer_t* buffer_obj);
void free_complex_buffer(complex_buffer_t* buffer);

void print_complex_buffer(complex_buffer_t* buffer);