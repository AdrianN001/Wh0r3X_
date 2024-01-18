#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h> 
#include <unistd.h>

#include "../lib/user.h"

char* generate_username_command(const char* username, const char* realname){
    char* buffer = (char*)malloc(sizeof(char) * 64);
    buffer[0] = 'U';
    buffer[1] = 'S';
    buffer[2] = 'E';
    buffer[3] = 'R';
    buffer[4] = ' ';

    const size_t username_length = strlen(username);
    strcpy(&buffer[5], username);
    buffer[5+username_length] = ' ';
    buffer[5+username_length + 1] = '*';
    buffer[5+username_length + 2] = '*';
    buffer[5+username_length + 3] = ':';
    buffer[5+username_length + 4] = ' ';

    strcpy(&(buffer[5+username_length+5]), realname);
    size_t new_size = strlen(buffer);
    buffer[new_size ] = '\n';
    buffer[new_size + 1] = '\0';
    return buffer;
}
char* generate_nickname_command(const char* nickname){
    char* buffer = (char*)malloc(sizeof(char) * 32);
    buffer[0] = 'N';
    buffer[1] = 'I';
    buffer[2] = 'C';
    buffer[3] = 'K';
    buffer[4] = ' ';

    strcpy(&(buffer[5]), nickname);
    size_t new_size = strlen(buffer);
    buffer[new_size ] = '\n';
    buffer[new_size + 1] = '\0';
    return buffer;

}

void init_user(struct user* new_user, char* nickname, char* username, char* realname){
    strcpy(new_user->nickname, nickname);
    strcpy(new_user->username, username);
    strcpy(new_user->realname, realname);
    new_user->conn = (struct server_conn){0};

}

void* registration_worker(void* vargp){

    printf("ASDASDD");
    struct user* session_user = (struct user*)vargp;

    const char* username_command = generate_username_command(session_user->username, session_user->realname);
    const char* nickname_command = generate_nickname_command(session_user->nickname);

    write(session_user->conn.sockfd, username_command, strlen(username_command));
    write(session_user->conn.sockfd, nickname_command, strlen(nickname_command));


    free((void*)username_command);
    free((void*)nickname_command);

    return NULL;

}


void connect_to_server(struct user* session_user, const char* host,int port){
    memset(&(session_user->conn), 0, sizeof(struct server_conn));

    int status = connect_server_to_endpoint(&(session_user->conn), host, port, CONNECT_BY_HOSTNAME);
  

    if (status != 0){
        printf("fatal error while joining the server\n");
        exit(1);
    }

    printf("asd");

    const char* username_command = generate_username_command(session_user->username, session_user->realname);
    const char* nickname_command = generate_nickname_command(session_user->nickname);

    send(session_user->conn.sockfd, username_command, strlen(username_command),0);
    send(session_user->conn.sockfd, nickname_command, strlen(nickname_command),0);


    free((void*)username_command);
    free((void*)nickname_command);

    char buffer[128] = {0};
    for (;;){
        memset(buffer, 0, sizeof(buffer));
        size_t bytes_read = read(session_user->conn.sockfd, buffer, sizeof(buffer));
        if(!bytes_read){
            break;
        }

        printf("recieved: %s\n", buffer);

    }

}
