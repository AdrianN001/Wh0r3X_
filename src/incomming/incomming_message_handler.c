#include "../../lib/incomming/incomming_message_handler.h"
#include "incomming_message_actions.c"
#include <stdbool.h>

void initialize_incomming_verb_pairs(){
    incomming_pairs[0] = (irc_incomming_verb_pair_t){
        .verb_name = "JOIN",
        .callback = incomming_join
    };
    incomming_pairs[1] = (irc_incomming_verb_pair_t){
        .verb_name = "PRIVMSG  ",
        .callback = incomming_privmsg_in_channel
    };

    incomming_pairs[2] = (irc_incomming_verb_pair_t){
        .verb_name = "PRIVMSG #",
        .callback = incomming_privmsg_betwwen_users
    };
    incomming_pairs[3] = (irc_incomming_verb_pair_t){
        .verb_name = "MSG",
        .callback = incomming_msg
    };
    incomming_pairs[4] = (irc_incomming_verb_pair_t){
        .verb_name = "PART",
        .callback = incomming_part
    };
}

void group_to_the_proper_tab(struct user* session_user, char* author_tag, char* args){

    char verb[12] = {0};
    char verb_args[256] = {0};
    sscanf(args, "%s %[a-zA-Z0-9.?~!/-+://@<>() ]", verb, verb_args);

    bool found_the_proper_channel = false;

    for (int i = 0; i < 32; i++){
        irc_incomming_verb_pair_t* current_pair = &(incomming_pairs[i]);
        if (strcmp(verb, current_pair->verb_name) == 0){

            found_the_proper_channel = current_pair->callback(session_user, author_tag, args);
            break;
        }
    }
}