#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h> 
#include "../lib/server_conn.h"

struct in_addr resolve_ip_address_from_hostname(const char* hostname){
    struct addrinfo hint;
    struct addrinfo *result;

    memset(&hint, 0, sizeof(hint));

    hint.ai_family = AF_INET; // set result to IPv4
    hint.ai_socktype = SOCK_STREAM; // TCP connection
    
    
    int status = getaddrinfo(hostname, NULL, &hint, &result);
    if (status != 0){
        printf("getaddrinfo failed!: %d\n", status);
        exit(1);
    }
    
    struct sockaddr_in* addr = NULL; 

    for (struct addrinfo* tmp = result; (tmp != NULL && addr == NULL) ; tmp = tmp->ai_next ){
        
        if( tmp->ai_family == AF_INET){
            addr = (struct sockaddr_in*)tmp->ai_addr;
        }
    }
    /*  Potential null pointer derefernce  */
    /*  Needs to be solved */
    struct in_addr address = addr->sin_addr;


    freeaddrinfo(result);
    return address;
}

int connect_server_to_endpoint(struct server_conn* new_connection, const char* host, int port, int connect_method){
    struct sockaddr_in servaddr;
    int temp_sockfd;

    // Create a socket descriptor
    temp_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (temp_sockfd < 0){
        printf("Couldn't initiliaze socket!\n");
        return temp_sockfd;
    }

    // Clear data in that region
    memset(&servaddr, 0, sizeof(servaddr));

    

    servaddr.sin_family = AF_INET;
    if(connect_method == CONNECT_BY_HOSTNAME){
        servaddr.sin_addr = resolve_ip_address_from_hostname(host);
    }else if(connect_method == CONNECT_BY_IPADDRESS) {
        servaddr.sin_addr.s_addr = inet_addr(host);
    }
    servaddr.sin_port = htons(port);

    // Connect to the host
    if(connect(temp_sockfd, (const struct sockaddr*)&servaddr, sizeof(servaddr) ) < 0){
        printf("Couldn't connect to the endpoint\n");
        return -1 ;
    }
    // Once everything succeded, the struct can have the descriptor
    new_connection->sockfd = temp_sockfd;
    return 0;
}




void leave_server(struct server_conn* connection){
   
    close(connection->sockfd);             /* kill the connection */
}