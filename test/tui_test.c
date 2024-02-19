#include <pthread.h>
#include <unistd.h>

#include "../src/tui/login_page.c"
#include "../src/tui/connection_popup.c"
#include "../src/tui/chat_page.c"

#include "../src/user.c"
#include "../src/message_handler.c"


#ifndef CTRL
#define CTRL(c) ((c) & 037)
#endif

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


WINDOW* information_box_debug(WINDOW* main_window){

   
    curs_set(0); /* Hide the cursor */

    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    
    return start_information_box(main_window, "irc.w3.org");
}
WINDOW* input_field_box_debug(WINDOW* main_window){
    return start_input_field_box(main_window);
}

WINDOW* users_box_debug(WINDOW* main_window){

    char* buffer[24] = {"valami23", "smtg23"};
    int size_of_buffer = 2;
    pthread_mutex_t lock; 
    pthread_mutex_init(&lock, NULL);

    
    curs_set(0); /* Hide the cursor */

    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    
    return start_users_box(main_window, buffer, &size_of_buffer, &lock);

    
}

int main(){
    WINDOW* main_window;
    struct user session_user = {0};
    add_new_tab(&session_user, GREETING_PAGE_TAB_NAME);


    srand(time(NULL));  

    char* buffer[24] = {"valami23", "reci23"};
    int size_of_buffer = 2;


    initialize_verb_pairs();

    complex_buffer_t history_buffer = create_complex_buffer(50);

    
    pthread_mutex_t users_gui_lock; 
    pthread_mutex_init(&users_gui_lock, NULL);

    pthread_mutex_t history_buffer_lock;
    pthread_mutex_init(&history_buffer_lock, NULL);


    if ( (main_window = initscr()) == NULL ) {
	    fprintf(stderr, "Error initialising ncurses.\n");
	    exit(1);
    }

    start_color();
    initialize_color_pairs();

<<<<<<< HEAD

=======
>>>>>>> dae8b1de63ea7bca3e8945be142d3b3b66be6762


    /* Create new user */
    login_result_t res = start_login_page(main_window);
    init_user(&session_user, "valami", "valami", "adrian rael");
    clear();
    /* Connect to new server */
    
    char* server_name = start_connection_popup_box(main_window);
    connect_user_to_server(&session_user, server_name, 6667);
    clear();

<<<<<<< HEAD
=======

    worker_thread_args_t history_buffer_fill_worker = {
        .buffer = &history_buffer,
        .lock = &history_buffer_lock,
        .session_user = &session_user,
    };

    pthread_t worker_thread_id; 
    pthread_create(&worker_thread_id, NULL, &fill_buffer_with_incomming_text, &history_buffer_fill_worker);
>>>>>>> dae8b1de63ea7bca3e8945be142d3b3b66be6762


    WINDOW* info_box = information_box_debug(main_window);
    WINDOW* users_box = users_box_debug(main_window);
    WINDOW* input_box = input_field_box_debug(main_window);
    WINDOW* history_box = start_history_box_window(main_window);
    WINDOW* active_tabs = start_tabs_box(main_window);

    nodelay(input_box, true); // Causes getch to be non-blocking

    form_buffer_t input_buffer = create_buffer(128);

//  event loop
    for(;;){

        int key_pressed = wgetch(input_box);
        switch(key_pressed){
            case ERR:
                goto UPDATE;
                break;
            case 0x0A: /* Enter ( actually the NL ) */{
                if (input_buffer.size == 0) { break; }

                /* Clear the window  */
                for( int y = 0; y < 50; y++){
                    wmove(input_box, y, 0);          // move to begining of line
                    wclrtoeol(input_box);          // clear line
                }
                // clrtoeol clears the border 
                box(input_box, 0, 0);


                send_message(&session_user, input_buffer.buffer);
                //append_to_buffer(&input_buffer, '\n');
                //append_to_complex_buffer(&history_buffer, input_buffer.buffer);
                clear_buffer(&input_buffer);
                break;
            }
            case CTRL('p'):{
                start_connection_popup_box(main_window);
                break;
            }
            default:{
                update_input_box(input_box, (char)key_pressed, &input_buffer);
            }
        }

UPDATE:
        update_info_box(info_box);
        update_users_box(users_box, buffer, &size_of_buffer, &users_gui_lock);
        update_history_box(history_box,&session_user.list_of_active_channels_head->buffer, &history_buffer_lock);
        update_tabs_box(active_tabs, &session_user);


        
        

        /*  Update them */
        wrefresh(users_box);
        wrefresh(info_box);
        wrefresh(input_box);
        wrefresh(history_box);
        wrefresh(active_tabs);
        usleep(5 * 10e2);
    }

    
}