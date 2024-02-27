#include "../../lib/tui/form_buffer.h"
#include <stdlib.h>
#include <string.h>

form_buffer_t create_buffer(const int max_size){
    char* new_buffer = (char*)malloc(sizeof(char) * max_size);
    memset(new_buffer, 0, max_size*sizeof(char));
    return (form_buffer_t){
        .buffer = new_buffer,
        .size = 0,
        .current_pointer = 0,
        .max_size = max_size
    };
}
void append_to_buffer(form_buffer_t* buffer_obj, char new_char){
    if(buffer_obj->size >= buffer_obj->max_size){
        return;
    }

    if (buffer_obj->current_pointer == buffer_obj->size){
        buffer_obj->buffer[buffer_obj->size++]=new_char;
        buffer_obj->buffer[buffer_obj->size]='\0';
        buffer_obj->current_pointer++;
        return;
    }
    buffer_obj->size++;
    for (int i = buffer_obj->size; i >= buffer_obj->current_pointer; i--){
        buffer_obj->buffer[i] = buffer_obj->buffer[i - 1];
    }
    buffer_obj->buffer[buffer_obj->current_pointer] = new_char;
    buffer_obj->current_pointer++;
}
void pop_from_buffer(form_buffer_t* buffer_obj){
    if (buffer_obj->size < 1){return ;}
    else if (buffer_obj->size == buffer_obj->current_pointer) {
        buffer_obj->buffer[buffer_obj->size--] = '\0';
        buffer_obj->current_pointer--;
    }
    else{
        for(int i = buffer_obj->current_pointer; i < buffer_obj->size; i++){
            buffer_obj->buffer[i] = buffer_obj->buffer[i+1];
        }
        buffer_obj->buffer[buffer_obj->size--] = '\0';
    }
}
void copyn(form_buffer_t* dest_buffer, char* src, short n){
    strncpy(dest_buffer->buffer, src, n);
    dest_buffer->buffer[n] = 0;
    for(size_t i = n+1; i<dest_buffer->max_size;i++){dest_buffer->buffer[i] = '\0';} // clear the remaining part
    
}
void move_pointer_to_right(form_buffer_t* buffer){
    if (buffer->current_pointer != buffer->size) 
        buffer->current_pointer++;
}
void move_pointer_to_left(form_buffer_t* buffer){
    if (buffer->current_pointer != 0)
        buffer->current_pointer--;
}
void extract(form_buffer_t* src_buffer, char* dest){
    src_buffer->buffer[src_buffer->size] = '\0';
    strncpy(dest, src_buffer->buffer, strlen(src_buffer->buffer));
}
void clear_buffer(form_buffer_t* buffer){
    memset(buffer->buffer, 0, sizeof(char)*buffer->size);
    buffer->size = 0;
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
