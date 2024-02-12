#include "../../lib/incomming/incomming_message_actions.h"
#include "../complex_buffer.c"
#include "../user.c"
#include "../tab.c"

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
void join( struct user* current_user, char* author_tag, char* args){
    char channel_name[32] = {0};
    sscanf(args,":%s", channel_name);

    int user_is_in_the_channel = linked_list_contains(current_user->list_of_active_channels_head, channel_name);
    if (user_is_in_the_channel != -1){
        char buffer[256] = {0};
        sprint(buffer, "%s joined this channel.", author_tag);
        tab_t* channel_tab = get_tab(current_user->list_of_active_channels_head, channel_name);
        
        append_to_complex_buffer( channel_tab->buffer, buffer );
    }
}

/*
    Sends a private message to nickname without opening a query window.

    @param: 
        - target
        - message
*/
void msg( struct user* current_user, char* author_tag, char* args){
    char channel_name[32] = {0};
    char body[256] = {0};
    sscanf(args,"%s :%s", channel_name, body);

    int user_is_in_the_channel = linked_list_contains(current_user->list_of_active_channels_head, channel_name);
    if (user_is_in_the_channel != -1){
        char buffer[316] = {0};
        sprint(buffer, "%s:%s", author_tag, body);
        tab_t* channel_tab = get_tab(current_user->list_of_active_channels_head, channel_name);
        
        append_to_complex_buffer( channel_tab->buffer, buffer );
    }
}

/*
    Leaves a channel that you are on.

    @param: 
        - channel
*/
void part( struct user* current_user, char* author_tag, char* args){
    char channel_name[32] = {0};
    sscanf(args,"%s :%s", channel_name, body);

    int user_is_in_the_channel = linked_list_contains(current_user->list_of_active_channels_head, channel_name);
    if (user_is_in_the_channel != -1){
        char buffer[316] = {0};
        sprint(buffer, "%s left the channel.", author_tag);
        tab_t* channel_tab = get_tab(current_user->list_of_active_channels_head, channel_name);
        
        append_to_complex_buffer( channel_tab->buffer, buffer );
    }
}

/*
    Sends a private message to nickname that will open a query window for the other user.

    @param: 
        - target
        - message
*/
void privmsg( struct user* current_user, char* author_tag, char* args){

   char channel_name[32] = {0};
    char body[256] = {0};
    sscanf(args,"%s :%s", channel_name, body);

    int user_is_in_the_channel = linked_list_contains(current_user->list_of_active_channels_head, channel_name);
    if (user_is_in_the_channel != -1){
        char buffer[316] = {0};
        sprint(buffer, "%s:%s", author_tag, body);
        tab_t* channel_tab = get_tab(current_user->list_of_active_channels_head, channel_name);
        
        append_to_complex_buffer( channel_tab->buffer, buffer );
    }
}

/*
    Opens a query window to this nickname and sends them a private message.

     @param: 
        - nickname
        - message
*/
void query( struct user* current_user, char* args){
    assert(0);
}

