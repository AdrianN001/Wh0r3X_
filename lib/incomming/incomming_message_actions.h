#pragma once
#include "../user.h"


/*
    Leaves a message indicating that you are currently not paying attention to IRC. 
    When someone sends you a message, they will automatically see your away message. 
    Using /AWAY with no message marks you as no longer being away and removes your previous message.

    example:  /away Off to get something to eat, back in a moment.

    @param: 
        -msg 
        
*/
bool incomming_away( struct user* current_user, char* author_tag, char* args);

/*
    Invites a nickname to a channel that you are on.

    @param: 
        - nickname
        - channel
*/
bool incomming_invite( struct user* current_user, char* args);

/*
    Joins the specified channel.
    example:  /join #irchelp

    Some channels may also have keys ie. a password, which you need to specify when using the /join command.
    example:  /join #irchelp trout

    @param: 
        - channel
        - password
*/
bool incomming_join( struct user* current_user,  char* author_tag,char* args);

/*
    Lists currently available channels.
    example:        /list

    @param: 
        - list of channels
*/
bool incomming_list( struct user* current_user, char* args);

/*
    Sends an action message to the current channel or query window. 
    To send an action message to a specific channel or nickname, see the /describe command.

    @param: 
        - message
*/
bool incomming_me( struct user* current_user, char* args);

/*
    Sends a private message to nickname without opening a query window.

    @param: 
        - target
        - message
*/
bool incomming_msg( struct user* current_user, char* author_tag, char* args);

/*
    Changes your nickname to a new nickname.

    @param: 
        - new_nickname
*/
bool incomming_nickname( struct user* current_user, char* args);

/*
    Sends a notice to the specified user. Like a /msg, but usually makes a sound.

    @param: 
        - nickname
        - message
*/
bool incomming_notice( struct user* current_user,char* args);

/*
    Leaves a channel that you are on.

    @param: 
        - channel
*/
bool incomming_part( struct user* current_user, char* author_tag, char* args);

/*
    Sends a private message to nickname that will open a query window for the other user.

    @param: 
        - target
        - message
*/
bool incomming_privmsg( struct user* current_user, char* author_tag, char* args);

/*
    Opens a query window to this nickname and sends them a private message.

    @param: 
        - nickname
        - message
*/
bool incomming_query( struct user* current_user, char* args);

/*
    Disconnects you from IRC and will give the optional message as the reason for your departure. 
    (this message only appears to people who are on the same channels as you).

    @param: 
        - message
*/
bool incomming_quit( struct user* current_user, char* args);

/*
    Changes the topic for a channel that you are on.

    @param: 
        - channel
        - topic
*/
bool incomming_topic( struct user* current_user, char* args);

/*
    Shows you information about a nickname.

    @param: 
        - nickname
*/
bool incomming_whois( struct user* current_user, char* args );