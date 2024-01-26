#include "../src/tui/login_page.c"
#include "../src/tui/connection_popup.c"
#include "../src/tui/chat_page.c"
#include <pthread.h>

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


void information_box_debug(WINDOW* main_window){

   
    curs_set(0); /* Hide the cursor */

    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    
    start_information_box(main_window, "irc.w3.org");


    delwin(main_window);
    endwin();
    refresh();
}

void users_box_debug(WINDOW* main_window){

    char* buffer[24] = {"valami23", "nigger23"};
    int size_of_buffer = 2;
    pthread_mutex_t lock; 
    pthread_mutex_init(&lock, NULL);

    
    curs_set(0); /* Hide the cursor */

    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    
    start_users_box(main_window, buffer, &size_of_buffer, &lock);

    pthread_mutex_destroy(&lock);

    delwin(main_window);
    endwin();
    refresh();
}

int main(){
    //start_connection_page_test();
    //users_box_debug();
    WINDOW* main_window;

    if ( (main_window = initscr()) == NULL ) {
	    fprintf(stderr, "Error initialising ncurses.\n");
	    exit(1);
    }
    information_box_debug(main_window);
    users_box_debug(main_window);

    for(;;){}

    /*
    char* server = start_connection_page_test();
    printf("%s\n", server);
    free(server);
    */
}