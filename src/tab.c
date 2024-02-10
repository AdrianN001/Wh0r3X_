#include "../lib/tab.h"

void add_new_tab(struct user* session_user, char* name){
    tab_t* empty_tab = (tab_t*)malloc(sizeof(tab_t));
    empty_tab->buffer = create_complex_buffer(48);
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
;
    if (strcmp(head->next->name, name) == 0){   // Check for at the very last item
        return true;
    }

    tab_t* temp = head->next;
    head->next = head->next->next; // jump one
    free_tab(temp);
    return false;

}
bool linked_list_contains(tab_t* head, char* name){
    if (!head){
        return false;
    }
    
    while(head->next != NULL){
        if ( strcmp( head->name, name) == 0){
            return true;
        }
        head = head->next;
    }

    return false;
}

void free_tab(tab_t* free_tab){
    free_complex_buffer(&free_tab->buffer);
    free((void*)free_tab);
}