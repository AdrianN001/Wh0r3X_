#include "../src/tui/login_page.c"
#include "../src/tui/connection_popup.c"

void start_connection_page_test(){
    WINDOW* main_window;

    if ( (main_window = initscr()) == NULL ) {
	    fprintf(stderr, "Error initialising ncurses.\n");
	    exit(1);
    }
    curs_set(0); /* Hide the cursor */

    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    start_connection_popup_box(main_window);

    delwin(main_window);
    endwin();
    refresh();
}

int main(){
    //start_login_page();
    start_connection_page_test();
}