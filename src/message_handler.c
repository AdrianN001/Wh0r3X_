#include "message_actions.c"
#include "../lib/message_handler.h"

void initialize_verb_pairs(){

    pairs[0] = (irc_verb_pair_t){
        .verb_name = "away",
        .callback = away,
    };
    pairs[1] = (irc_verb_pair_t){
        .verb_name = "invite",
        .callback = invite,
    };
    pairs[2] = (irc_verb_pair_t){
        .verb_name = "join",
        .callback = join,
    };
    pairs[3] = (irc_verb_pair_t){
        .verb_name = "list",
        .callback = list,
    };
    pairs[4] = (irc_verb_pair_t){
        .verb_name = "me",
        .callback = me,
    };
    pairs[5] = (irc_verb_pair_t){
        .verb_name = "msg",
        .callback = msg,
    };
    pairs[6] = (irc_verb_pair_t){
        .verb_name = "nickname",
        .callback = nickname,
    };
    pairs[7] = (irc_verb_pair_t){
        .verb_name = "notice",
        .callback = notice,
    };
    pairs[8] = (irc_verb_pair_t){
        .verb_name = "part",
        .callback = part,
    };
    pairs[9] = (irc_verb_pair_t){
        .verb_name = "privmsg",
        .callback = privmsg,
    };
    pairs[10] = (irc_verb_pair_t){
        .verb_name = "query",
        .callback = query,
    };
    pairs[11] = (irc_verb_pair_t){
        .verb_name = "quit",
        .callback = quit,
    };
    pairs[12] = (irc_verb_pair_t){
        .verb_name = "topic",
        .callback = topic,
    };
    pairs[13] = (irc_verb_pair_t){
        .verb_name = "whois",
        .callback = whois,
    };
}

void send_message(struct user* current_user, char* buffer){

    
    if (buffer[0] == '/') {
        // That's a command

        char verb[16] = {0};
        char args[256] = {0};
        sscanf(buffer, "/%s %[a-zA-Z0-9.?~!#+: ]", verb, args);

        if (*verb == 0) return;

        for (int i = 0; i < 32; i++){
            irc_verb_pair_t current_pair = pairs[i];
            if(strcmp(verb, current_pair.verb_name) == 0){
                current_pair.callback(current_user, args);
                break;
            }
        }

    }else{

        // It is a message

    }
   
}


