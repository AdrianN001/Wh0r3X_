#pragma once
#include <pthread.h>

struct server_conn{
    int sockfd;
    char* ping_pong_phrase; 
    pthread_t thread_id;
};

#define CONNECT_BY_IPADDRESS 0
#define CONNECT_BY_HOSTNAME  1

int connect_server_to_endpoint(struct server_conn* new_connection, const char* host, int port, int connection_methond);


void leave_server(struct server_conn* connection);