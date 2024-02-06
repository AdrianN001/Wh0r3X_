#include "../lib/history_buffer.h"
#include <string.h>

history_buffer_t create_history_buffer(const int max_size){
    char** new_buffer = (char**)malloc(sizeof(char*) * max_size);
    return (history_buffer_t){
        .buffer = new_buffer,
        .size = 0,
        .max_size = max_size
    };
}
void append_to_history_buffer(history_buffer_t* buffer_obj, char* new_buffer){
    if(buffer_obj->size < buffer_obj->max_size){

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
}
void append_to_history_buffer_with_size(history_buffer_t* buffer_obj, char* new_buffer, size_t n){
    if(buffer_obj->size < buffer_obj->max_size){
        buffer_obj->buffer[buffer_obj->size] = malloc(sizeof(char)* n+1);
        strncpy(buffer_obj->buffer[buffer_obj->size], new_buffer, n );
        buffer_obj->buffer[buffer_obj->size][n] = '\0';
        buffer_obj->size++;
    }
}
void pop_from_history_buffer(history_buffer_t* buffer_obj){
    if (buffer_obj->size < 1){return;}
    char* last_buffer = buffer_obj->buffer[buffer_obj->size-1];
    free(last_buffer);
    buffer_obj->size--;
}
void free_history_buffer(history_buffer_t* free_buffer){
    for (int i = 0; i<free_buffer->size;i++){
        free(free_buffer->buffer[i]);
    }
    free(free_buffer->buffer);

}

void print_history_buffer(history_buffer_t* buffer){
    for (int i = 0; i < buffer->size; i++){
        printf("%d:\t%s\n", i, buffer->buffer[i]);
    }
    printf("\n");
}
