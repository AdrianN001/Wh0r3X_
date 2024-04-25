#include <stdlib.h>
#include <string.h>
#include "whorex/user.h"

void add_new_tab(struct user* session_user, char* name){
    tab_t* empty_tab = (tab_t*)malloc(sizeof(tab_t));
    empty_tab->buffer = create_complex_buffer(48);
    empty_tab->users = create_complex_buffer(40);
    strcpy(empty_tab->name, name);
    empty_tab->name[strlen(name)] = '\0';
    empty_tab->next = NULL;

    if(session_user->list_of_active_channels_head == NULL){
        session_user->list_of_active_channels_head = empty_tab;
        session_user->current_channel = empty_tab;
        return;
    }
    tab_t* head = session_user->list_of_active_channels_head;
    while(head->next != NULL){
        head = head->next;
    }
    head->next = empty_tab;
}

tab_t* get_tab(tab_t* head, char* name){
    while(head != NULL){ // Check for in the middle
        if (!strncmp(head->name, name, strlen(name))){
            return head;
        }
        head = head->next;
    }
    return NULL;
}

bool remove_tab(struct user* session_user, char* name){

   
    tab_t* head = session_user->list_of_active_channels_head;
    if(!strcmp(head->name, name)){ // Check for the first one
        

        tab_t* temp = head;
        session_user->list_of_active_channels_head = temp->next;
        free_tab(temp);
        
        return true;

    }
    if(head->next == NULL){
        return false;
    }
    while(head->next->next != NULL){ // Check for in the middle
        head = head->next;
        if (strcmp(head->next->name, name) == 0){
            tab_t* remove = head->next;
            tab_t* next_one = head->next->next;
            free_tab(head->next);
            head->next = next_one;
            return true;
        }
    }
    if (strcmp(head->next->name, name) == 0){   // Check for at the very last item
        free_tab(head->next);
        head->next = (tab_t*)NULL;
        return true;
    }

    return false;

}
int linked_list_contains(tab_t* head, char* name){
    if (!head){
        return -1;
    }
    int index = 0;
    while(head != NULL){
        if ( strcmp( head->name, name) == 0){
            return index;
        }
        head = head->next;
        index++;
    }

    return -1;
}

void free_tab(tab_t* free_tab){
    free_complex_buffer(&free_tab->buffer);
    free((void*)free_tab);
}
