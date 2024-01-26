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
    strcpy(buffer, "USER ");
    const size_t username_length = strlen(username);
    strcpy(&buffer[5], username);
    strcpy(&(buffer[5 + username_length]), " 0 * :");
   
   size_t new_size_without_realname = strlen(buffer);

    strcpy(&(buffer[new_size_without_realname]), realname);
    size_t new_size = strlen(buffer);
    buffer[new_size ] = '\n';
    buffer[new_size + 1] = '\0';
    return buffer;
}
char* generate_nickname_command(const char* nickname){
    char* buffer = (char*)malloc(sizeof(char) * 32);
    strcpy(buffer, "NICK ");

    strcpy(&(buffer[5]), nickname);
    size_t new_size = strlen(buffer);
    buffer[new_size ] = '\n';
    buffer[new_size + 1] = '\0';
    return buffer;

}

void init_user(struct user* new_user, char* nickname, char* username, char* realname){
    new_user->nickname = malloc(sizeof(char) * 32);
    new_user->username = malloc(sizeof(char) * 32);
    new_user->realname = malloc(sizeof(char) * 32);
    
    strncpy(new_user->nickname, nickname, strlen(nickname));
    strncpy(new_user->username, username, strlen(username));
    strncpy(new_user->realname, realname, strlen(realname));
    new_user->conn = (struct server_conn){0};

}

void* registration_worker(void* vargp){

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


    const char* username_command = generate_username_command(session_user->username, session_user->realname);
    const char* nickname_command = generate_nickname_command(session_user->nickname);

    send(session_user->conn.sockfd, username_command, strlen(username_command),0);
    send(session_user->conn.sockfd, nickname_command, strlen(nickname_command),0);


    free((void*)username_command);
    free((void*)nickname_command);

    char buffer[512] = {0};
    for (;;){
        memset(buffer, 0, sizeof(buffer));
        size_t bytes_read = read(session_user->conn.sockfd, buffer, sizeof(buffer));
        if(!bytes_read){
            break;
        }
        printf("recieved: %s\n", buffer);
    }
}

void free_user(struct user* _del_user){
    free(_del_user->nickname);
    free(_del_user->realname);
    free(_del_user->username);
}


void leave_server_as_user(struct user* session_user){

    const char* leave_command = "QUIT";
    write(session_user->conn.sockfd, leave_command, strlen(leave_command));
    
    leave_server(&(session_user->conn));
    free_user(session_user);
    
}