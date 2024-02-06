#pragma once
#include "../src/server_conn.c"
#include "history_buffer.h"

struct user{ 
    char* nickname;
    char* username;
    char* realname;

    struct server_conn conn;
};

void init_user(struct user* new_user,char* nickname, char* username, char* realname);

void change_nickname(struct user* session_user, char* new_nickname);

void connect_user_to_server(struct user* session_user, const char* host,int port);

typedef struct {
    struct user* session_user; 
    history_buffer_t* buffer;
    pthread_mutex_t* lock;
} worker_thread_args_t;

// Thread Worker Function 
void* fill_buffer_with_incomming_text(void* args);
void leave_server_as_user(struct user* session_user);

void free_user(struct user* _del_user);