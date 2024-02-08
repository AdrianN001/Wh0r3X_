#pragma once
#include <pthread.h>

#define DEFAULT_PORT_FOR_IRC_SERVER 6667

struct server_conn{
    int sockfd;
    char* ping_pong_phrase; 
    pthread_t thread_id;
};

#define CONNECT_BY_IPADDRESS 0
#define CONNECT_BY_HOSTNAME  1

int create_connection(struct server_conn* new_connection, const char* host, int port, int connection_methond);
void send_text_to_server(struct server_conn* connection, char* buffer);


void leave_server(struct server_conn* connection);