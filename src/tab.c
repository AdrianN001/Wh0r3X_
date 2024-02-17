#ifndef TAB 
#define TAB

#include "../lib/tab.h"

void add_new_tab(struct user* session_user, char* name){
    tab_t* empty_tab = (tab_t*)malloc(sizeof(tab_t));
    empty_tab->buffer = create_complex_buffer(48);
    empty_tab->users = create_complex_buffer(40);
    strcpy(empty_tab->name, name);
    empty_tab->next = NULL;

    if(session_user->list_of_active_channels_head == NULL){
        session_user->list_of_active_channels_head = empty_tab;
        return;
    }

    tab_t* head = session_user->list_of_active_channels_head;
    while(head->next != NULL){
        head = head->next;
    }
    head->next = empty_tab;
}

tab_t* get_tab(tab_t* head, char* name){
    if(!strcmp(head->name, name)){ // Check for the first one
        return head;

    }
    while(head->next->next != NULL){ // Check for in the middle
        head = head->next;
        if (strcmp(head->next->name, name) == 0){
            return head->next;
        }
    }

    if (strcmp(head->next->name, name) == 0){   // Check for at the very last item
        return head->next;
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
    while(head->next->next != NULL){ // Check for in the middle
        head = head->next;
        if (strcmp(head->next->name, name) == 0){
            return true;
        }
    }
    if (strcmp(head->next->name, name) == 0){   // Check for at the very last item
        return true;
    }

    tab_t* temp = head->next;
    head->next = head->next->next; // jump one
    free_tab(temp);
    return false;

}
int linked_list_contains(tab_t* head, char* name){
    if (!head){
        return false;
    }
    
    int index = 0;
    while(head->next != NULL){
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

#endif