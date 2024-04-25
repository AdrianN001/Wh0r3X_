#ifndef __USER_H_
#define __USER_H_

#include "server_conn.h"
#include "complex_buffer.h"
#include "complex_buffer.h"
#include <stdbool.h>
#define GREETING_PAGE_TAB_NAME "greeting_page"


typedef struct tab{
    char name[32];

    complex_buffer_t buffer;
    complex_buffer_t users;
    struct tab* next;
} tab_t;

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

void free_user(struct user* _del_user);



void add_new_tab(struct user* session_user, char* name);
tab_t* get_tab(tab_t* head, char* name);

/*
    Returns whether it found the given tab
*/
bool remove_tab(struct user* session_user, char* name);

/*
    Returns the index of the tab
*/
int linked_list_contains(tab_t* head, char* name);
void free_tab(tab_t* free_tab);



typedef struct {
    struct user* session_user; 
    complex_buffer_t* buffer;
    pthread_mutex_t* lock;
} worker_thread_args_t;

// Thread Worker Function 
void* fill_buffer_with_incomming_text(void* args);
void leave_server_as_user(struct user* session_user);

#endif