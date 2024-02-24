#ifndef FORMAT
#define FORMAT

#include "incomming/incomming_message_handler.c"
#include "../lib/format.h"
#include "time.c"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifndef CLR_REG
#define CLR_REG "\e[1;1H\e[2J"
#endif


char* try_format_response(struct user* session_user, char* response_buffer, char* out){
    
    // User Action
    char username[32] = {0};
    char nickname[32] = {0};
    char host[128] = {0};
    char body[316] = {0};


    // User Action
    sscanf(response_buffer, ":%[a-zA-Z0-9/_-.]!%[a-zA-Z0-9_-~]@%[a-zA-Z0-9_.-]%[a-zA-Z0-9.-?~!+:_# ]", nickname, username, host, body);
    
    
    if(*username != 0 && *nickname != 0 && *host != 0 && *body != 0){
        // Create author
        char reformatted_text[516] = {0};
        char author_tag[64] = {0};
        char time_tag[32] = {0};
        fetch_current_time_h_m(time_tag);
        sprintf(author_tag, "<%s>|<%s:[%s]>", time_tag, nickname, username);
        const size_t size_of_author_tag = strlen(out);

        
        // It groups the response to the tab
        group_to_the_proper_tab(session_user, nickname, author_tag, body);

        // Finalize
        strcpy(out, "");
        return out;
    }
    // Server Action
    char server_name[32] = {0};
    char numeric[5] = {0};
    char target_user[128] = {0};

    sscanf(response_buffer, ":%[a-zA-Z0-9/-.] %[0-9] %[a-zA-Z0-9/-.] %[a-zA-Z0-9.?~!/-+://@<>() ]", server_name, numeric, target_user, body);
    if (*server_name != 0 && *numeric != 0 && *target_user != 0 && *body != 0){
        char reformatted_text[516] = {0};
        tab_t* greeting_page_tab = get_tab(session_user->list_of_active_channels_head, GREETING_PAGE_TAB_NAME);
        assert(greeting_page_tab != NULL)
        size_t bytes_written = sprintf(reformatted_text, "<server>: %s", body);
        strcpy(out, "");
        strcpy(out, reformatted_text);
        append_to_complex_buffer(&greeting_page_tab->buffer, out);
        out[bytes_written] = '\0';
        return out;
    }

    

}

int check_for_ping(char* response_buffer, char* ping_buffer){
    char ping_phrase[32] = {0};
    char verb[64] = {0};

    sscanf(response_buffer, "%s :%s",verb, ping_phrase);
    if(strcmp(verb, "PING") != 0 ){
        return (int)NULL;
    }
    sprintf(ping_buffer, "PONG :%s\n", ping_phrase);
    return 1;
}

int format_and_group_incomming_messages(struct user* session_user, char* temp_buffer){
    complex_buffer_t messages_with_line_breaks = create_complex_buffer(6);
    append_to_complex_buffer_with_line_break(&messages_with_line_breaks,temp_buffer);
    char out[512] = {0};
    for (int i = 0; i < messages_with_line_breaks.size; i++){
        try_format_response(session_user, messages_with_line_breaks.buffer[i], out);
        strcpy(messages_with_line_breaks.buffer[i], out);
    }
}


#endif