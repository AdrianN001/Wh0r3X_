#include "../../lib/tui/form_buffer.h"
#include <stdlib.h>
#include <string.h>

form_buffer_t create_buffer(const int max_size){
    char* new_buffer = (char*)malloc(sizeof(char) * max_size);
    memset(new_buffer, 0, max_size*sizeof(char));
    return (form_buffer_t){
        .buffer = new_buffer,
        .size = 0,
        .max_size = max_size
    };
}
void append_to_buffer(form_buffer_t* buffer_obj, char new_char){
    if(buffer_obj->size < buffer_obj->max_size){
        buffer_obj->buffer[buffer_obj->size++]=new_char;
    }
}
char pop_from_buffer(form_buffer_t* buffer_obj){
    if (buffer_obj->size < 1){return '0';}
    char* last_element_pointer = &(buffer_obj->buffer[buffer_obj->size-1]);
    char last_element = *last_element_pointer;
    *last_element_pointer = '\0';
    buffer_obj->size--;
    return last_element;
}
void copyn(form_buffer_t* dest_buffer, char* src, short n){
    strncpy(dest_buffer->buffer, src, n);
    for(size_t i = n+1; i<dest_buffer->max_size;i++){dest_buffer->buffer[i] = '\0';} // clear the remaining part
    
}
void extract(form_buffer_t* src_buffer, char* dest){
    src_buffer->buffer[src_buffer->size] = '\0';
    strncpy(dest, src_buffer->buffer, strlen(src_buffer->buffer));
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
