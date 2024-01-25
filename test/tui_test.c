#include "../src/tui/login_page.c"
#include "../src/tui/connection_popup.c"
#include "../src/tui/chat_page.c"

char* start_connection_page_test(){
    WINDOW* main_window;

    if ( (main_window = initscr()) == NULL ) {
	    fprintf(stderr, "Error initialising ncurses.\n");
	    exit(1);
    }
    curs_set(0); /* Hide the cursor */

    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    char* server = start_connection_popup_box(main_window);

    delwin(main_window);
    endwin();
    refresh();
    return server;
}


void information_box_debug(){
    WINDOW* main_window;

    if ( (main_window = initscr()) == NULL ) {
	    fprintf(stderr, "Error initialising ncurses.\n");
	    exit(1);
    }
    curs_set(0); /* Hide the cursor */

    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    
    start_information_box(main_window);


    delwin(main_window);
    endwin();
    refresh();
}

int main(){
    information_box_debug();

    /*
    char* server = start_connection_page_test();
    printf("%s\n", server);
    free(server);
    */
}