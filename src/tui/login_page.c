#include "../../lib/tui/login_page.h"
#include "form_buffer.c"
#include <stdlib.h>
#include <string.h>


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

    int x_center = (POPUP_WINDOW_COLS - POPUP_WINDOW_WIDTH)  / 2;
    int y_center = (POPUP_WINDOW_ROW - POPUP_WINDOW_HEIGHT) / 2;
    
    printf("asdasd");
        
    popup_window = subwin(main_window, POPUP_WINDOW_HEIGHT, POPUP_WINDOW_WIDTH, y_center, x_center);    
    keypad(popup_window, TRUE);
    box(popup_window, 0, 0);
    mvwaddstr(popup_window, 1, 24, "Welcome, and enjoy your stay!" );

    mvwaddstr(popup_window, 4, 2, "user_name:");
    mvwaddstr(popup_window, 6, 2, "nick_name:");
    mvwaddstr(popup_window, 8, 2, "real name:");

    keypad(popup_window, TRUE);

    wrefresh(popup_window);

    int activate_form = USERNAME_FORM;

    form_buffer_t input_buffers[3] = { 
                                    create_buffer(), /* username */
                                    create_buffer(), /* nickname */
                                    create_buffer()  /* realname*/
                                    }; 

    while(1){
        char key_pressed = getch();

        switch(key_pressed){
            case 0x09: /* TAB */
                activate_form = (activate_form + 1) % 3; 
                break;
            case 127:
                exit(1);
            case '\b':
                exit(1);
            case 0x0F: /* Enter */
                exit(1);
                break;
        }
        
        /* Update the buffer */
        form_buffer_t* active_buffer = &(input_buffers[activate_form]);
        append_to_buffer(active_buffer, key_pressed);
                
        /* Update the UI */
        mvwaddch(popup_window, 4 + (activate_form * 2), 12 + active_buffer->size, key_pressed);
        wrefresh(popup_window);
    }
CLEANING_UP:
    /* Cleaning up */
    delwin(popup_window);
    delwin(main_window);
    endwin();
    refresh();
    return (login_result_t){0};
}