#pragma once
#include "../src/server_conn.c"

struct user{ 
    char* nickname;
    char* username;
    char* realname;

    struct server_conn conn;
};

void init_user(struct user* new_user,char* nickname, char* username, char* realname);

void change_nickname(struct user* session_user, char* new_nickname);

void connect_to_server(struct user* session_user, const char* host,int port);
void leave_server_as_user(struct user* session_user);

void free_user(struct user* _del_user);