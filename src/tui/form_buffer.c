#include "../../lib/tui/form_buffer.h"
#include <stdlib.h>
#include <string.h>

form_buffer_t create_buffer(){
    return (form_buffer_t){
        .buffer = malloc(sizeof(char) * BUFFER_SIZE),
        .size = 0
    };
}
void append_to_buffer(form_buffer_t* buffer_obj, char new_char){
    if(buffer_obj->size < BUFFER_SIZE){
        buffer_obj->buffer[buffer_obj->size++]=new_char;
    }
}
char pop_from_buffer(form_buffer_t* buffer_obj){
    char* last_element_pointer = &(buffer_obj->buffer[buffer_obj->size-1]);
    char last_element = *last_element_pointer;
    last_element_pointer = '\0';
    buffer_obj->size--;
    return last_element;
}
void copyn(form_buffer_t* dest_buffer, char* src, short n){
    for (int i = 0; i < n;i++){
        src[i] = dest_buffer->buffer[i];
    }
}
void extract(form_buffer_t* src_buffer, char* dest){
    src_buffer->buffer[src_buffer->size] = '\0';
    strcpy(dest, src_buffer->buffer);
}
void free_buffer(form_buffer_t* free_buffer){
    free(free_buffer->buffer);
}

void print(form_buffer_t* buffer){
    for (int i = 0; i < buffer->size; i++){
        printf("%c", buffer->buffer[i]);
    }
    printf("\n");
}
