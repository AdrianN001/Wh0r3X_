#ifndef COMPLEX_BUFFER
#define COMPLEX_BUFFER

#include "../lib/complex_buffer.h"
#include <string.h>

#define NOT_FOUND -1

complex_buffer_t create_complex_buffer(const int max_size){
    char** new_buffer = (char**)malloc(sizeof(char*) * max_size);
    return (complex_buffer_t){
        .buffer = new_buffer,
        .size = 0,
        .starting_point = 0,
        .max_size = max_size
    };
}

void append_to_complex_buffer(complex_buffer_t* buffer_obj, char* new_buffer){
    
    if(buffer_obj->size == buffer_obj->max_size){ 
        strcpy(buffer_obj->buffer[buffer_obj->starting_point], new_buffer);
        buffer_obj->starting_point = (buffer_obj->starting_point + 1) % buffer_obj->max_size;
        return;
    }
    
    size_t size_of_the_new_buffer = strlen(new_buffer);

    buffer_obj->buffer[buffer_obj->size] = malloc(sizeof(char)* size_of_the_new_buffer);
    memset(buffer_obj->buffer[buffer_obj->size], 0, sizeof(char)* size_of_the_new_buffer);
    strncpy(buffer_obj->buffer[buffer_obj->size], new_buffer, strlen(new_buffer));
    buffer_obj->size++;
}

int complex_buffer_contains(complex_buffer_t* buffer, char* searched_buffer){
    for (int i = 0; i < buffer->size; i++){
        char* curr_buff = buffer->buffer[i];
        if (!strcmp(curr_buff, searched_buffer)){
            return i;
        }
    }
    return -1;
}

void append_to_complex_buffer_with_line_break(complex_buffer_t* buffer_obj, char* new_buffer){
    if(buffer_obj->size == buffer_obj->max_size){

        char* token = strtok(new_buffer, "\n");

        while(token != NULL){
            size_t size_of_the_new_buffer = strlen(token);
            strncpy(buffer_obj->buffer[buffer_obj->starting_point], token, size_of_the_new_buffer );
            buffer_obj->buffer[buffer_obj->starting_point][size_of_the_new_buffer] = '\0';
            buffer_obj->starting_point = (buffer_obj->starting_point + 1) % buffer_obj->max_size;
            token = strtok(NULL, "\n");
        }
        return;
    }

    char* token = strtok(new_buffer, "\n");
    
    while(token != NULL){
        size_t size_of_the_new_buffer = strlen(token);
        buffer_obj->buffer[buffer_obj->size] = malloc(sizeof(char)* size_of_the_new_buffer);

        strncpy(buffer_obj->buffer[buffer_obj->size], token, size_of_the_new_buffer );
        buffer_obj->buffer[buffer_obj->size][size_of_the_new_buffer] = '\0';
        buffer_obj->size++;
        token = strtok(NULL, "\n");
    }
    
}
void append_to_complex_buffer_with_size(complex_buffer_t* buffer_obj, char* new_buffer, size_t n){
     if(buffer_obj->size >= buffer_obj->max_size){ 
        strncpy(buffer_obj->buffer[buffer_obj->starting_point], new_buffer, n);
        buffer_obj->starting_point = (buffer_obj->starting_point + 1) % buffer_obj->max_size;
        return;
    }

    buffer_obj->buffer[buffer_obj->size] = malloc(sizeof(char)* n+1);
    strncpy(buffer_obj->buffer[buffer_obj->size], new_buffer, n );
    buffer_obj->buffer[buffer_obj->size][n] = '\0';
    buffer_obj->size++;
    
}
void pop_from_complex_buffer(complex_buffer_t* buffer_obj){
    if (buffer_obj->size < 1){return;}
    char* last_buffer = buffer_obj->buffer[buffer_obj->size-1];
    free(last_buffer);
    buffer_obj->size--;
}

int remove_from_complex_buffer(complex_buffer_t* buffer, char* removed_buffer){
    int index = NOT_FOUND;
    for (int i = 0; i < buffer->size; i++){
        char* curr_buff = buffer->buffer[i];
        if (!strcmp(curr_buff, removed_buffer)){
            index = i;
            free(buffer->buffer[i]);
            buffer->buffer[i] = NULL;
            buffer->size--;
            continue;
        }
        if (index != NOT_FOUND){
            buffer->buffer[i-1] = buffer->buffer[i];
        }
    }
    if (index != NOT_FOUND){
        buffer->buffer[buffer->size -1] = buffer->buffer[buffer->size];
    }
    
    return index;
}
void free_complex_buffer(complex_buffer_t* free_buffer){
    for (int i = 0; i<free_buffer->size;i++){
        free(free_buffer->buffer[i]);
    }
    free(free_buffer->buffer);

}

void print_complex_buffer(complex_buffer_t* buffer){
    for (int i = 0; i < buffer->size; i++){
        printf("%d:\t %s (%p)\n", i, buffer->buffer[i], &(buffer->buffer[i]));
    }
    printf("\n");
}

#endif