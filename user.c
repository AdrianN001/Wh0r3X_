#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h> 
#include <unistd.h>

#include "lib/user.h"

char* generate_username_command(const char* username, const char* realname){
    char* buffer = (char*)malloc(sizeof(char) * 64);
    buffer[0] = 'U';
    buffer[1] = 'S';
    buffer[2] = 'E';
    buffer[3] = 'R';
    buffer[4] = ' ';

    const size_t username_length = strlen(username);
    memcpy(&buffer[5], username, username_length);
    buffer[5+username_length] = ' ';
    buffer[5+username_length + 1] = '*';
    buffer[5+username_length + 2] = '*';
    buffer[5+username_length + 3] = ':';
    buffer[5+username_length + 4] = ' ';

    const size_t realname_length = strlen(realname);
    memcpy(&buffer[5+username_length+5], realname, realname_length);
    return buffer;
}
char* generate_nickname_command(const char* nickname){
    char* buffer = (char*)malloc(sizeof(char) * 32);
    buffer[0] = 'N';
    buffer[1] = 'I';
    buffer[2] = 'C';
    buffer[3] = 'K';
    buffer[4] = ' ';

    memcpy(&buffer[5], nickname, strlen(nickname));
    return buffer;

}

void init_user(struct user* new_user, char* nickname, char* username, char* realname){
    new_user->nickname = nickname;
    new_user->username = username;
    new_user->realname = realname;
    new_user->conn = (struct server_conn){0};

}
void connect_to_server(struct user* session_user, const char* host,int port){
    memset(&(session_user->conn), 0, sizeof(session_user));

    connect_server_to_endpoint(&(session_user->conn), host, port, CONNECT_BY_IPADDRESS);

    char buffer[128];
    const char* username_command = generate_username_command(session_user->username, session_user->realname);
    const char* nickname_command = generate_nickname_command(session_user->nickname);
    memset(buffer, 0, sizeof(buffer));
    write(session_user->conn.sockfd, username_command , strlen(username_command));
    write(session_user->conn.sockfd, nickname_command, strlen(nickname_command));

    free(username_command);
    free(nickname_command);
}


void free_user(struct user* _del_user){
    free(_del_user->nickname);
    free(_del_user->realname);
    free(_del_user->username);
}