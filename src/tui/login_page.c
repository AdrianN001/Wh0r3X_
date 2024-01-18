#include "../../lib/tui/login_page.h"
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

    wrefresh(popup_window);

    while(1);
    /* Cleaning up */
    delwin(popup_window);
    delwin(main_window);
    endwin();
    refresh();
    return (login_result_t){0};
}