#include "../lib/format.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


char* try_format_response(char* response_buffer){

    char username[32] = {0};
    char nickname[32] = {0};
    char host[128] = {0};
    char body[316] = {0};

    sscanf(response_buffer, ":%[a-zA-Z0-9/-.]!%[a-zA-Z0-9~]@%[a-zA-Z0-8.] %[a-zA-Z0-9.?~!+: ]", nickname, username, host, body);
    
    
    if(*username == 0 &&  *nickname == 0 &&  *host == 0 && *body == 0){
        return response_buffer;
    }
    // Create author
    char author_tag[64];
    sprintf(author_tag, "<%s:[%s]>", nickname, username);
    if (!strcmp(nickname, "adrian")){
        printf("%s\n", author_tag);
    }

}
