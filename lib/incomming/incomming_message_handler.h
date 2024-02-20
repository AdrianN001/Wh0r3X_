#pragma once
#include "../user.h"

typedef struct {
    char verb_name[16];
    bool(*callback)(struct user*, char* author_tag, char* args);
} irc_incomming_verb_pair_t;


/* The pairs are used for searching */
static irc_incomming_verb_pair_t incomming_pairs[32] = {0};

void initialize_incomming_verb_pairs();
void group_to_the_proper_tab(struct user* session_user, char* nickname, char* author_tag, char* args);

