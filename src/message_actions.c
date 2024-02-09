#include "../lib/message_actions.h"
#include "user.c"


#ifndef assert
#define assert(x) if((!(x))){printf("assertion error!\n error at %s() function\n",__func__); exit(1);}
#endif


/*
    Leaves a message indicating that you are currently not paying attention to IRC. 
    When someone sends you a message, they will automatically see your away message. 
    Using /AWAY with no message marks you as no longer being away and removes your previous message.

    example:  /away Off to get something to eat, back in a moment.

    @param: 
        -msg 
        
*/
void away( struct user* current_user, char* args){
    char buffer[64] = {0}; 
    memset(buffer, 0, 64 * sizeof(char));
    sprintf(buffer, "AWAY %s", args);

    send_text_to_server(&current_user->conn, buffer);
}

/*
    Invites a nickname to a channel that you are on.

    @param: 
        - nickname
        - channel
*/
void invite( struct user* current_user, char* args){

    char nickname[32] = {0};
    char channel[256] = {0};
    sscanf(args, "%s %s", nickname, channel);

    char buffer[64] = {0}; 
    memset(buffer, 0, 64 * sizeof(char));
    sprintf(buffer, "INVITE %s %s", nickname, channel);

    send_text_to_server(&current_user->conn, buffer);
}

/*
    Joins the specified channel.
    example:  /join #irchelp

    Some channels may also have keys ie. a password, which you need to specify when using the /join command.
    example:  /join #irchelp trout

    @param: 
        - channel
        - password
*/
void join( struct user* current_user, char* args){

    char channel[32] = {0};
    char passwd[32] = {0};
    sscanf(args, "%s %s", channel, passwd);

    assert(channel[0] == '#');

    

    char buffer[64] = {0}; 
    memset(buffer, 0, 64 * sizeof(char));
    sprintf(buffer, "JOIN %s %s", channel, passwd);

    int index_of_the_channel = complex_buffer_contains(&(current_user->active_channels), channel);
    if (index_of_the_channel >= 0 ){
        current_user->current_channel = current_user->active_channels.buffer[index_of_the_channel]; 
    }else{
        append_to_complex_buffer(&(current_user->active_channels), channel);
        current_user->current_channel = current_user->active_channels.buffer[current_user->active_channels.size - 1]; 
    }
    send_text_to_server(&current_user->conn, buffer);
}

/*
    Lists currently available channels.
    example:        /list

    @param: 
        - list of channels
*/
void list( struct user* current_user, char* args){

    char buffer[] = "LIST";

    send_text_to_server(&current_user->conn, buffer);
}

/*
    Sends an action message to the current channel or query window. 
    To send an action message to a specific channel or nickname, see the /describe command.

    @param: 
        - message
*/
void me( struct user* current_user, char* args){
    assert(0);
}


/*
    Sends a private message to nickname without opening a query window.

    @param: 
        - target
        - message
*/
void msg( struct user* current_user, char* args){

    char target[16] = {0};
    char message[256] = {0};
    sscanf(args, "/%s %s", target, message);


    char buffer[256] = {0}; 
    memset(buffer, 0, 256 * sizeof(char));
    sprintf(buffer, "MSG %s %s", (strcmp(target, "") != 0) ? target : current_user->current_channel, message);

    send_text_to_server(&current_user->conn, buffer);
}

/*
    Changes your nickname to a new nickname.

    @param: 
        - new_nickname
*/
void nickname( struct user* current_user, char* args){
    char buffer[64] = {0}; 
    memset(buffer, 0, 64 * sizeof(char));
    sprintf(buffer, "NICK %s", args);


    change_nickname(current_user, args);

    send_text_to_server(&current_user->conn, buffer);
}

/*
    Sends a notice to the specified user. Like a /msg, but usually makes a sound.

    @param: 
        - nickname
        - message
*/
void notice( struct user* current_user,char* args){

    char nickname[16] = {0};
    char message[256] = {0};
    sscanf(args, "/%s %s", nickname, message);

    char buffer[64] = {0}; 
    memset(buffer, 0, 64 * sizeof(char));
    sprintf(buffer, "NOTICE %s %s", nickname, message);

    send_text_to_server(&current_user->conn, buffer);
}

/*
    Leaves a channel that you are on.

    @param: 
        - channel
*/
void part( struct user* current_user, char* args){
    char buffer[64] = {0}; 
    memset(buffer, 0, 64 * sizeof(char));
    sprintf(buffer, "PART %s", args);

    remove_from_complex_buffer(&(current_user->active_channels), args);
    current_user->current_channel = current_user->active_channels.buffer[0];
    send_text_to_server(&current_user->conn, buffer);
}

/*
    Sends a private message to nickname that will open a query window for the other user.

    @param: 
        - target
        - message
*/
void privmsg( struct user* current_user, char* args){

    char target[16] = {0};
    char message[256] = {0};
    sscanf(args, "/%s %s", target, message);


    char buffer[256] = {0}; 
    memset(buffer, 0, 256 * sizeof(char));
    sprintf(buffer, "PRIVMSG %s %s", target, message);

    send_text_to_server(&current_user->conn, buffer);
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

/*
    Disconnects you from IRC and will give the optional message as the reason for your departure. 
    (this message only appears to people who are on the same channels as you).

    @param: 
        - message
*/
void quit( struct user* current_user, char* args){
    char buffer[] = "QUIT";
    send_text_to_server(&current_user->conn, buffer);
}

/*
    Changes the topic for a channel that you are on.

    @param: 
        - channel
        - topic
*/
void topic( struct user* current_user, char* args){


    char channel[16] = {0};
    char topic[256] = {0};
    sscanf(args, "/%s %s", channel, topic);

    char buffer[64] = {0}; 
    memset(buffer, 0, 64 * sizeof(char));
    sprintf(buffer, "TOPIC %s %s", channel, topic);

    send_text_to_server(&current_user->conn, buffer);
}

/*
    Shows you information about a nickname.

    @param: 
        - nickname
*/
void whois( struct user* current_user, char* args ){
    char buffer[64] = {0}; 
    memset(buffer, 0, 64 * sizeof(char));
    sprintf(buffer, "WHOIS %s", args);

    send_text_to_server(&current_user->conn, buffer);
}