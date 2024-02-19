#pragma once
#include "../src/server_conn.c"
#include "complex_buffer.h"
#include "tab.h"

struct user{ 
    char* nickname;
    char* username;
    char* realname;

    struct server_conn conn;
    
    tab_t* current_channel;
    int active_channels;

    tab_t* list_of_active_channels_head; // linked list
};

void init_user(struct user* new_user,char* nickname, char* username, char* realname);

void change_nickname(struct user* session_user, char* new_nickname);

void connect_user_to_server(struct user* session_user, const char* host,int port);

typedef struct {
    struct user* session_user; 
    complex_buffer_t* buffer;
    pthread_mutex_t* lock;
} worker_thread_args_t;

// Thread Worker Function 
void* fill_buffer_with_incomming_text(void* args);
void leave_server_as_user(struct user* session_user);

void free_user(struct user* _del_user);