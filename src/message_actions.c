#include "../lib/message_actions.h"
#include "user.c"
#include "tab.c"

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
    sprintf(buffer, "AWAY %s\n", args);

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
    sprintf(buffer, "INVITE %s %s\n", nickname, channel);

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
    sprintf(buffer, "JOIN %s %s\n", channel, passwd);

    

    int index = linked_list_contains(current_user->list_of_active_channels_head, channel);
    if(index == -1){
        add_new_tab(current_user, channel);
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
    sscanf(args, "%s %[a-zA-Z0-9.?~!+: ]", target, message);


    char buffer[256] = {0}; 
    memset(buffer, 0, 256 * sizeof(char));
    sprintf(buffer, "MSG %s %s\n", (strcmp(target, "") != 0) ? target : current_user->current_channel->name, message);

    send_text_to_server(&current_user->conn, buffer);
}

/*
    Changes your nickname to a new nickname.

    @param: 
        - new_nickname
*/
void nickname( struct user* current_user, char* args){
    char buffer[64] = {0}; 
    sprintf(buffer, "NICK %s\n", args);

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
    sscanf(args, "%s %s", nickname, message);

    char buffer[64] = {0}; 
    memset(buffer, 0, 64 * sizeof(char));
    sprintf(buffer, "NOTICE %s %s\n", nickname, message);

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
    sprintf(buffer, "PART %s\n", args);


    bool found = remove_tab(current_user, args);
    if (found){
        current_user->current_channel = current_user->list_of_active_channels_head;
        send_text_to_server(&current_user->conn, buffer);
    }
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
    sscanf(args, "%s %[a-zA-Z0-9.?~!+: ]", target, message);


    char buffer[256] = {0}; 
    memset(buffer, 0, 256 * sizeof(char));
    sprintf(buffer, "PRIVMSG %s :%s\n", target, message);

    send_text_to_server(&current_user->conn, buffer);
}

void custom_privmsg(struct user* session_user, char* target, char* body){
    char buffer[316] = {0};
    sprintf(buffer, "PRIVMSG %s :%s\n", target, body);
    send_text_to_server(&session_user->conn, buffer);
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
    char buffer[] = "QUIT\n";
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
    sscanf(args, "%s %[a-zA-Z0-9.?~!+: ]", channel, topic);

    char buffer[64] = {0}; 
    memset(buffer, 0, 64 * sizeof(char));
    sprintf(buffer, "TOPIC %s %s\n", channel, topic);

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
    sprintf(buffer, "WHOIS %s\n", args);

    send_text_to_server(&current_user->conn, buffer);
}