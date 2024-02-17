#pragma once
#include "complex_buffer.h"
#include <stdbool.h>

#define GREETING_PAGE_TAB_NAME "greeting_page"

typedef struct tab{
    char name[32];

    complex_buffer_t buffer;
    complex_buffer_t users;
    struct tab* next;
} tab_t;

#include "user.h" // Not the best method

void add_new_tab(struct user* session_user, char* name);
tab_t* get_tab(tab_t* head, char* name);

/*
    Returns whether it found the given tab
*/
bool remove_tab(struct user* session_user, char* name);

/*
    Returns the index of the tab
*/
int linked_list_contains(tab_t* head, char* name);
void free_tab(tab_t* free_tab);