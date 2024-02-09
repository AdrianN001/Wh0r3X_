#pragma once
#include "user.h"



typedef struct {
    char verb_name[16];
    void(*callback)(struct user*, char*);
} irc_verb_pair_t;


/* The pairs are used for searching */
static irc_verb_pair_t pairs[32] = {0};

void initialize_verb_pairs();

void send_message(struct user* current_user, char* buffer);
