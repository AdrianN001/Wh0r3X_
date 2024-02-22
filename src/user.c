#ifndef USER
#define USER

#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h> 
#include <unistd.h>


#include "../lib/user.h"
#include "complex_buffer.c"
#include "format.c"


char* generate_username_command(const char* username, const char* realname){
    /* Not the greatest, and most well-written code that I've ever wrote, I have to admit*/
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

void change_nickname(struct user* session_user, char* new_nickname){
    strcpy(session_user->nickname, "");
    strncpy(session_user->nickname, new_nickname, strlen(new_nickname));
    strncpy(session_user->nickname, new_nickname, strlen(new_nickname));
}

void init_user(struct user* new_user, char* nickname, char* username, char* realname){
    new_user->nickname = malloc(sizeof(char) * 32);
    new_user->username = malloc(sizeof(char) * 32);
    new_user->realname = malloc(sizeof(char) * 32);
    
    strncpy(new_user->nickname, nickname, strlen(nickname));
    strncpy(new_user->username, username, strlen(username));
    strncpy(new_user->realname, realname, strlen(realname));

    new_user->current_channel = NULL;
    new_user->conn = (struct server_conn){0};

}



void connect_user_to_server(struct user* session_user, const char* host,int port){
    memset(&(session_user->conn), 0, sizeof(struct server_conn));

    int status = create_connection(&(session_user->conn), host, port, CONNECT_BY_HOSTNAME);
  
    if (status != 0){
        printf("fatal error while joining the server\n");
        exit(1);
    }


    const char* username_command = generate_username_command(session_user->username, session_user->realname);
    const char* nickname_command = generate_nickname_command(session_user->nickname);

    write(session_user->conn.sockfd, username_command, strlen(username_command));
    write(session_user->conn.sockfd, nickname_command, strlen(nickname_command));


    free((void*)username_command);
    free((void*)nickname_command);

   
}


void* fill_buffer_with_incomming_text(void* args){

    worker_thread_args_t* args_with_type = (worker_thread_args_t*)args;

    struct user* session_user = args_with_type->session_user;
    complex_buffer_t* main_buffer = args_with_type->buffer;
    pthread_mutex_t* lock = args_with_type->lock;

    initialize_incomming_verb_pairs();

    char temp_buffer[MAX_MESSAGE_LENGTH] = {0};
    for (;;){
        memset(temp_buffer, 0, sizeof(temp_buffer));
        size_t bytes_read = read(session_user->conn.sockfd, temp_buffer, sizeof(temp_buffer));
        if(!bytes_read){
            break;
        }
        format_and_group_incomming_messages(session_user, temp_buffer);
        int size_of_pong_phrase;
        if ((size_of_pong_phrase = check_for_ping(temp_buffer, session_user->conn.ping_pong_phrase)) != 0){
            write(session_user->conn.sockfd, session_user->conn.ping_pong_phrase, strlen(session_user->conn.ping_pong_phrase));
        }
       
    }
    free_complex_buffer(main_buffer);
    return NULL;
}

void free_user(struct user* _del_user){
    free(_del_user->nickname);
    free(_del_user->realname);
    free(_del_user->username);

    tab_t* current;
    while(_del_user->list_of_active_channels_head != NULL){
        current = _del_user->list_of_active_channels_head;
        _del_user->list_of_active_channels_head = _del_user->list_of_active_channels_head->next;
        free_tab(current);
    }
    
}


void leave_server_as_user(struct user* session_user){

    const char* leave_command = "QUIT";
    write(session_user->conn.sockfd, leave_command, strlen(leave_command));
    
    leave_server(&(session_user->conn));
    free_user(session_user);
    
}

#endif