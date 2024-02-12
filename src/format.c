#ifndef FORMAT
#define FORMAT

#include "../lib/format.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


bool group_incomming_message(struct user* session_user, char* response_buffer){

}

char* try_format_response(char* response_buffer){
    
    // User Action
    char username[32] = {0};
    char nickname[32] = {0};
    char host[128] = {0};
    char body[316] = {0};


    // User Action
    sscanf(response_buffer, ":%[a-zA-Z0-9/-.]!%[a-zA-Z0-9~]@%[a-zA-Z0-9/-.] %[a-zA-Z0-9.?~!+: ]", nickname, username, host, body);
    
    
    if(*username != 0 && *nickname != 0 && *host != 0 && *body != 0){
            // Create author
        char reformatted_text[516] = {0};

        sprintf(reformatted_text, "<%s:[%s]>", nickname, username);
        const size_t size_of_author_tag = strlen(reformatted_text);

        // Finalize
        strcpy(response_buffer, "");
        strcpy(response_buffer, reformatted_text);
        return response_buffer;
    }
    // Server Action
    char server_name[32] = {0};
    char numeric[5] = {0};
    char target_user[128] = {0};

    sscanf(response_buffer, ":%[a-zA-Z0-9/-.] %[0-9] %[a-zA-Z0-9/-.] %[a-zA-Z0-9.?~!/-+://@<>() ]", server_name, numeric, target_user, body);
    if (*server_name != 0 && *numeric != 0 && *target_user != 0 && *body != 0){
        char reformatted_text[516] = {0};

        sprintf(reformatted_text, "<server>: %s", body);
        strcpy(response_buffer, "");
        strcpy(response_buffer, reformatted_text);
        return response_buffer;

    }

    

}

int check_for_ping(char* response_buffer, char* ping_buffer){
    char ping_phrase[32] = {0};
    char verb[64] = {0};

    sscanf(response_buffer, "%s :%s",verb, ping_phrase);
    if(strcmp(verb, "PING") != 0 ){
        return NULL;
    }
    sprintf(ping_buffer, "PONG :%s", ping_phrase);
    return 1;
}

#endif