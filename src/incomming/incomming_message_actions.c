#include "../../lib/incomming/incomming_message_actions.h"
#include "../complex_buffer.c"
#include "../user.c"
#include "../tab.c"
#include <stdio.h>

#ifndef assert
#define assert(x) if((!(x))){printf("assertion error!\n error at %s() function\n",__func__); exit(1);}
#endif



/*
    Joins the specified channel.
    example:  /join #irchelp

    Some channels may also have keys ie. a password, which you need to specify when using the /join command.
    example:  /join #irchelp trout

    @param: 
        - channel
        - password
*/
bool incomming_join( struct user* current_user, char* author_tag, char* args){
    char channel_name[32] = {0};
    sscanf(args,":%s", channel_name);
    
    int user_is_in_the_channel = linked_list_contains(current_user->list_of_active_channels_head, channel_name);
    if (user_is_in_the_channel != -1){
        char buffer[256] = {0};
        sprintf(buffer, "%s joined this channel.", author_tag);
        tab_t* channel_tab = get_tab(current_user->list_of_active_channels_head, channel_name);
        append_to_complex_buffer( &channel_tab->buffer, buffer );
        return true;
    }

    return false;
}

/*
    Sends a private message to nickname without opening a query window.

    @param: 
        - target
        - message
*/
bool incomming_msg( struct user* current_user, char* author_tag, char* args){
    char channel_name[32] = {0};
    char msg[256] = {0};
    sscanf(args,"%s :%[a-zA-Z0-9.?~!/-+://@<>() ]", channel_name, msg);

    int user_is_in_the_channel = linked_list_contains(current_user->list_of_active_channels_head, channel_name);
    if (user_is_in_the_channel != -1){
        char buffer[316] = {0};
        sprintf(buffer, "%s:%s", author_tag, msg);
        tab_t* channel_tab = get_tab(current_user->list_of_active_channels_head, channel_name);
        
        append_to_complex_buffer( &channel_tab->buffer, buffer );
        return true;
    }
    return false;
}

/*
    Leaves a channel that you are on.

    @param: 
        - channel
*/
bool incomming_part( struct user* current_user, char* author_tag, char* args){
    char channel_name[32] = {0};
    sscanf(args,"%s :%s", channel_name);

    int user_is_in_the_channel = linked_list_contains(current_user->list_of_active_channels_head, channel_name);
    if (user_is_in_the_channel != -1){
        char buffer[316] = {0};
        sprintf(buffer, "%s has left the channel.", author_tag);
        tab_t* channel_tab = get_tab(current_user->list_of_active_channels_head, channel_name);
        
        append_to_complex_buffer( &channel_tab->buffer, buffer );
        return true;
    }
    return false;
}

/*
    Sends a private message to nickname that will open a query window for the other user.

    @param: 
        - target
        - message
*/
bool incomming_privmsg_in_channel( struct user* current_user, char* author_tag, char* args){
    char channel_name[32] = {0};
    char body[256] = {0};
    sscanf(args,"%s :%s", channel_name, body);

    int user_is_in_the_channel = linked_list_contains(current_user->list_of_active_channels_head, channel_name);
    if (user_is_in_the_channel != -1){
        char buffer[316] = {0};
        sprintf(buffer, "%s:%s", author_tag, body);
        tab_t* channel_tab = get_tab(current_user->list_of_active_channels_head, channel_name);
        
        append_to_complex_buffer( &channel_tab->buffer, buffer );
        return true;
    }
    return false;
}

bool incomming_privmsg_between_users( struct user* current_user, char* nickname_of_author, char* author_tag, char* args){
    char username[32] = {0};
    char body[256] = {0};
    sscanf(args,"%s :%s", username, body);

    int user_is_in_the_channel = linked_list_contains(current_user->list_of_active_channels_head, nickname_of_author);
    if (user_is_in_the_channel == -1){
        add_new_tab(current_user, nickname_of_author);
    }
    char buffer[316] = {0};
    sprintf(buffer, "*%s*:%s", nickname_of_author, body);
    assert(current_user != NULL && nickname_of_author != NULL);
    tab_t* channel_tab = get_tab(current_user->list_of_active_channels_head, nickname_of_author);
    append_to_complex_buffer( &channel_tab->buffer, buffer );
    return true;
    
}

/*
    Opens a query window to this nickname and sends them a private message.

     @param: 
        - nickname
        - message
*/
bool incomming_query( struct user* current_user, char* args){
    assert(0);
}

