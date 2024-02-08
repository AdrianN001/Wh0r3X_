#pragma once
#include "user.h"


/*
    Leaves a message indicating that you are currently not paying attention to IRC. 
    When someone sends you a message, they will automatically see your away message. 
    Using /AWAY with no message marks you as no longer being away and removes your previous message.

    example:  /away Off to get something to eat, back in a moment.
*/
void away( struct user* current_user, const char* msg);

/*
    Invites a nickname to a channel that you are on.
*/
void invite( struct user* current_user, const char* nickname, const char* channel);

/*
    Joins the specified channel.
    example:  /join #irchelp

    Some channels may also have keys ie. a password, which you need to specify when using the /join command.
    example:  /join #irchelp trout
*/
void join( struct user* current_user, const char* channel, const char* passwd);

/*
    Lists currently available channels.
    example:        /list
*/
void list( struct user* current_user, const char** channels);

/*
    Sends an action message to the current channel or query window. 
    To send an action message to a specific channel or nickname, see the /describe command.
*/
void me( struct user* current_user, const char* message);

/*
    Sends a private message to nickname without opening a query window.
*/
void msg( struct user* current_user, const char* nickname, const char* message);

/*
    Changes your nickname to a new nickname.
*/
void nickname( struct user* current_user, const char* new_nickname);

/*
    Sends a notice to the specified user. Like a /msg, but usually makes a sound.
*/
void notice( struct user* current_user, const char* nickname , const char* message);

/*
    Leaves a channel that you are on.
*/
void part( struct user* current_user, const char* channel);

/*
    Sends a private message to nickname that will open a query window for the other user.
*/
void privmsg( struct user* current_user, const char* target , const char* message);

/*
    Opens a query window to this nickname and sends them a private message.
*/
void query( struct user* current_user, const char* nickname , const char* message);

/*
    Disconnects you from IRC and will give the optional message as the reason for your departure. 
    (this message only appears to people who are on the same channels as you).
*/
void quit( struct user* current_user, const char* message);

/*
    Changes the topic for a channel that you are on.
*/
void topic( struct user* current_user, const char* channel , const char* topic);

/*
    Shows you information about a nickname.
*/
void whois( struct user* current_user, const char* nickname );