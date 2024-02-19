#pragma once
#define BUFFER_SIZE 32

typedef struct form_buffer{
    char* buffer;
    int size;
    int max_size;
} form_buffer_t;

form_buffer_t create_buffer(const int max_size);
void append_to_buffer(form_buffer_t* buffer_obj, char new_char);
char pop_from_buffer(form_buffer_t* buffer_obj);
void copyn(form_buffer_t* dest_buffer, char* src, short n);
void extract(form_buffer_t* src_buffer, char* dest);
void clear_buffer(form_buffer_t* buffer);
void free_buffer(form_buffer_t* buffer);

void print(form_buffer_t* buffer);