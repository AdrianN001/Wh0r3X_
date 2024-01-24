#include "../../lib/tui/login_page.h"
#include "form_buffer.c"
#include <stdlib.h>
#include <string.h>


void free_login_result(login_result_t* res){
    free(res->nickname);
    free(res->realname);
    free(res->username);
}

void print_login_result(login_result_t* res){
    printf("username => %s\n nickname => %s\n realname => %s\n", res->nickname, res->username, res->realname);
}



void print_background(WINDOW* window){
    FILE* file = fopen("assets/backgrounds/whorex3_grey_inv.txt", "r");
    if (file == NULL){
        return;
    }
    char buffer[256] = {0};

    while (fgets(buffer, sizeof(buffer), file)) {        
        for (int i = 0; i < strlen(buffer); i++){
            waddch(window,  buffer[i] | A_BOLD );
        }
    }
    refresh();
    fclose(file);

}

void set_cursor(WINDOW* window, short buffer_id, form_buffer_t* buffers){
    form_buffer_t* active_buffer = &(buffers[buffer_id]);
    int horizontal_offset = active_buffer->size;

    /* Clear the cursor from the previous */
    switch(buffer_id){
        case USERNAME_FORM:
            mvwaddch(window, 8, 12 + horizontal_offset, ' ');
            break;
        case NICKNAME_FORM:
            mvwaddch(window, 6, 12 + horizontal_offset, ' ');
            break;
        case REALNAME_FORM:
            mvwaddch(window, 4, 12 + horizontal_offset, ' ');
            break;
    }

    /* Set new cursor */
    mvwaddch(window, 4 + (buffer_id * 2), 12 + horizontal_offset, '|');
}


login_result_t start_login_page(){
    WINDOW* main_window, *popup_window; 

    if ( (main_window = initscr()) == NULL ) {
	    fprintf(stderr, "Error initialising ncurses.\n");
	    exit(1);
    }
    curs_set(0); /* Hide the cursor */

    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    print_background(main_window);

    int x_center = (POPUP_WINDOW_COLS - POPUP_WINDOW_WIDTH) / 2;
    int y_center = (POPUP_WINDOW_ROW - POPUP_WINDOW_HEIGHT) / 2;
    
        
    popup_window = subwin(main_window, POPUP_WINDOW_HEIGHT, POPUP_WINDOW_WIDTH, y_center, x_center);    
    keypad(popup_window, TRUE);
    box(popup_window, 0, 0);
    mvwaddstr(popup_window, 1, 24, "Welcome, and enjoy your stay!" );

    mvwaddstr(popup_window, USERNAME_FORM_POSITION, 2, "user_name:");
    mvwaddstr(popup_window, NICKNAME_FORM_POSITION, 2, "nick_name:");
    mvwaddstr(popup_window, REALNAME_FORM_POSITION, 2, "real name:");

    keypad(popup_window, TRUE);

    wrefresh(popup_window);

    int activate_form = USERNAME_FORM;

    form_buffer_t input_buffers[3] = { 
                                    create_buffer(), /* username */
                                    create_buffer(), /* nickname */
                                    create_buffer()  /* realname */
                                    }; 

    while(1){
        char key_pressed = getch();
        //mvwadd(popup_window, 1,1, (int)key_pressed);
        //exit(key_pressed);

        switch(key_pressed){
            case 0x09: /* TAB */
                activate_form = (activate_form + 1) % 3; 
                break;
            case 0x07:{ /* Backspace ( actually the BELL ) */
                
                /* Update the buffer */
                form_buffer_t* active_buffer = &(input_buffers[activate_form]);
                pop_from_buffer(active_buffer);

                /* Update the UI */
                mvwaddch(popup_window, USERNAME_FORM_POSITION + (activate_form * 2), 12+active_buffer->size , ' ');
            }
                break;        
            case 0x0A: /* Enter ( actually the NL ) */
                goto CLEANING_UP;
            case 0x03: /* Arrow up */
                exit(1);
            case 0x02: /* Arrow down */
                exit(1);
            default:{   
                /* Update the buffer */
                form_buffer_t* active_buffer = &(input_buffers[activate_form]);
                append_to_buffer(active_buffer, key_pressed);
                        
                /* Update the UI */
                mvwaddstr(popup_window, USERNAME_FORM_POSITION + (activate_form * 2), 12 , active_buffer->buffer);
            }
        }
        wrefresh(popup_window);
    }
CLEANING_UP:
    /* Cleaning up */
    delwin(popup_window);
    delwin(main_window);
    endwin();
    refresh();

    char* username_buffer_ext = (char*)malloc(sizeof(char) * 24);
    char* nickname_buffer_ext = (char*)malloc(sizeof(char) * 24);
    char* realname_buffer_ext = (char*)malloc(sizeof(char) * 24);

    strcpy(username_buffer_ext, input_buffers[0].buffer);
    strcpy(nickname_buffer_ext, input_buffers[1].buffer);
    strcpy(realname_buffer_ext, input_buffers[2].buffer);



    return (login_result_t){
        .username = username_buffer_ext,
        .nickname = nickname_buffer_ext,
        .realname = realname_buffer_ext
    };
}