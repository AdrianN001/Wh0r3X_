#include "../lib/message_actions.h"
#include "user.c"


/*
    Leaves a message indicating that you are currently not paying attention to IRC. 
    When someone sends you a message, they will automatically see your away message. 
    Using /AWAY with no message marks you as no longer being away and removes your previous message.

    example:  /away Off to get something to eat, back in a moment.
*/
void away( struct user* current_user, const char* msg){
    char buffer[64] = {0}; 
    memset(buffer, 0, 64 * sizeof(char));
    sprintf(buffer, "AWAY %s", msg);

    send_text_to_server(current_user->conn, buffer);
}

/*
    Invites a nickname to a channel that you are on.
*/
void invite( struct user* current_user, const char* nickname, const char* channel){
    char buffer[64] = {0}; 
    memset(buffer, 0, 64 * sizeof(char));
    sprintf(buffer, "INVITE %s %s", nickname, channel);

    send_text_to_server(current_user->conn, buffer);
}

/*
    Joins the specified channel.
    example:  /join #irchelp

    Some channels may also have keys ie. a password, which you need to specify when using the /join command.
    example:  /join #irchelp trout
*/
void join( struct user* current_user, const char* channel, const char* passwd){
    char buffer[64] = {0}; 
    memset(buffer, 0, 64 * sizeof(char));
    if (passwd == NULL){
        sprintf(buffer, "JOIN %s", channel);
    }else{
        sprintf(buffer, "JOIN %s %s", channel, passwd);
    }
    int index_of_the_channel = complex_buffer_contains(&(current_user->active_channels), channel);
    if (index_of_the_channel >= 0 ){
        current_user->current_channel = current_user->active_channels.buffer[index_of_the_channel]; 
    }else{
        append_to_complex_buffer(&(current_user->active_channels), channel);
        current_user->current_channel = current_user->active_channels.buffer[current_user->active_channels.size - 1]; 
    }
    send_text_to_server(current_user->conn, buffer);
}

/*
    Lists currently available channels.
    example:        /list
*/
void list( struct user* current_user, const char** channels){
    char buffer[] = "LIST"

    send_text_to_server(current_user->conn, buffer);
}

/*
    Sends an action message to the current channel or query window. 
    To send an action message to a specific channel or nickname, see the /describe command.
*/
void me( struct user* current_user, const char* message);

/*
    Sends a private message to nickname without opening a query window.
*/
void msg( struct user* current_user, const char* target, const char* message){
    char buffer[256] = {0}; 
    memset(buffer, 0, 256 * sizeof(char));
    sprintf(buffer, "MSG %s %s", (target != NULL) ? target : current_user->current_channel, message);

    send_text_to_server(current_user->conn, buffer);
}

/*
    Changes your nickname to a new nickname.
*/
void nickname( struct user* current_user, const char* new_nickname){
    char buffer[64] = {0}; 
    memset(buffer, 0, 64 * sizeof(char));
    sprintf(buffer, "NICK %s %s", new_nickname);


    change_nickname(current_user, new_nickname);

    send_text_to_server(current_user->conn, buffer);
}

/*
    Sends a private message to nickname without opening a query window for either you or them.
*/
void notice( struct user* current_user, const char* nickname , const char* message){
    char buffer[64] = {0}; 
    memset(buffer, 0, 64 * sizeof(char));
    sprintf(buffer, "NOTICE %s %s", nickname, channel);

    send_text_to_server(current_user->conn, buffer);
}

/*
    Leaves a channel that you are on.
*/
void part( struct user* current_user, const char* channel){
    char buffer[64] = {0}; 
    memset(buffer, 0, 64 * sizeof(char));
    sprintf(buffer, "PART %s", channel);

    remove_from_complex_buffer(&(current_user->active_channels), channel);
    send_text_to_server(current_user->conn, buffer);
}

/*
    Sends a private message to nickname that will open a query window for the other user.
*/
void privmsg( struct user* current_user, const char* target , const char* message){
    char buffer[256] = {0}; 
    memset(buffer, 0, 256 * sizeof(char));
    sprintf(buffer, "PRIVMSG %s %s", target, message);

    send_text_to_server(current_user->conn, buffer);
}

/*
    Opens a query window to this nickname and sends them a private message.
*/
void query( struct user* current_user, const char* nickname , const char* message);

/*
    Disconnects you from IRC and will give the optional message as the reason for your departure. 
    (this message only appears to people who are on the same channels as you).
*/
void quit( struct user* current_user, const char* message){
    char buffer[] = "QUIT";
    send_text_to_server(current_user->conn, buffer);
}

/*
    Changes the topic for a channel that you are on.
*/
void topic( struct user* current_user, const char* channel , const char* topic){
    char buffer[64] = {0}; 
    memset(buffer, 0, 64 * sizeof(char));
    sprintf(buffer, "TOPIC %s %s", channel, topic);

    send_text_to_server(current_user->conn, buffer);
}

/*
    Shows you information about a nickname.
*/
void whois( struct user* current_user, const char* nickname ){
    char buffer[64] = {0}; 
    memset(buffer, 0, 64 * sizeof(char));
    sprintf(buffer, "WHOIS %s", nickname);

    send_text_to_server(current_user->conn, buffer);
}