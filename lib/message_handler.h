#pragma once
#include "user.h"

typedef union{
    void(*one_parameter)(struct user*, char*);
    void(*two_parameter)(struct user*, char*, char*);
} message_handler_callback_t;

typedef struct {
    char verb_name[16];
    void(*callback)(struct user*, char*);
} irc_verb_pair_t;


/* The pairs are used for searching */
static irc_verb_pair_t pairs[32] = {0};

void initialize_verb_pairs();

void send_message(struct user* current_user, const char* buffer);
