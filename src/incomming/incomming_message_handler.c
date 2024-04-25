#include "whorex/incomming.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#ifndef CLR_REG
#define CLR_REG "\e[1;1H\e[2J"
#endif

#define PRIVMSG_INDX 1

void initialize_incomming_verb_pairs(){
    incomming_pairs[0] = (irc_incomming_verb_pair_t){
        .verb_name = "JOIN",
        .callback = incomming_join
    };
    incomming_pairs[PRIVMSG_INDX] = (irc_incomming_verb_pair_t){
        .verb_name = "PRIVMSG",
        .callback = NULL
    };
    incomming_pairs[2] = (irc_incomming_verb_pair_t){
        .verb_name = "MSG",
        .callback = incomming_msg
    };
    incomming_pairs[3] = (irc_incomming_verb_pair_t){
        .verb_name = "PART",
        .callback = incomming_part
    };
}

void group_to_the_proper_tab(struct user* session_user, char* nickname, char* author_tag, char* args){

    char verb[12] = {0};
    char verb_args[256] = {0};
    sscanf(args, "%s %[a-zA-Z0-9.?~!/-+:#//@<>() ]", verb, verb_args);
 
    bool found_the_proper_channel = false;
    
    

    for (int i = 0; i < 32; i++){
        irc_incomming_verb_pair_t* current_pair = &(incomming_pairs[i]);
        if (strcmp(verb, current_pair->verb_name) == 0){

            if(i == PRIVMSG_INDX){
                if (verb_args[0] == '#'){
                    incomming_privmsg_in_channel(session_user, author_tag, verb_args);
                }else{
                    incomming_privmsg_between_users(session_user, nickname, author_tag, verb_args);
                }
            }else{
                found_the_proper_channel = current_pair->callback(session_user, author_tag, verb_args);
                break;
            }
            
        }
    }
}