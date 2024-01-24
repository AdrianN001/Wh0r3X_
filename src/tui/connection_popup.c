#include "../../lib/tui/connection_popup.h"

connection_history_t get_connection_history(){
    char** temp_array = malloc(sizeof(char*) * 3);
    temp_array[0] = "irc.w3.org";
    temp_array[1] = "irc.dal.net";
    temp_array[2] = "test#3";

    return (connection_history_t){
        .data = temp_array,
        .size = 3,
    };
}
void free_connection_history(connection_history_t* history){
    free(history->data);
}


void print_border(WINDOW* popup_window){

    int x_center = (CONNECTION_POPUP_WINDOW_ROW + CONNECTION_POPUP_WINDOW_HEIGHT) / 1.8;

    for (int vertical = 2; vertical < 19; vertical++){
        mvwaddch(popup_window, vertical, x_center, '|' );
        mvwaddch(popup_window, vertical, x_center+1, '|' );
    }
}

void list_history(WINDOW* window, connection_history_t* history ){

    if ( history->size == 0){
        mvwaddstr(window, 8 , 46, "Hmmm. It seems, that...");
        mvwaddstr(window, 10, 40, "you haven't been on an irc server");
        mvwaddstr(window, 12, 53, "before");

        wrefresh(window);
        return;
    }

    for(int i = 0; i < history->size; i++){
        mvwaddstr(window, 8+i, 52, history->data[i]);
    }
    wrefresh(window);
}


void start_connection_popup_box(WINDOW *base_window){


    int x_center = (CONNECTION_POPUP_WINDOW_COLS - CONNECTION_POPUP_WINDOW_WIDTH) / 2;
    int y_center = (CONNECTION_POPUP_WINDOW_ROW - CONNECTION_POPUP_WINDOW_HEIGHT) / 2;

    WINDOW* popup_window = subwin(base_window, CONNECTION_POPUP_WINDOW_HEIGHT, CONNECTION_POPUP_WINDOW_WIDTH, y_center, x_center);    
    
    keypad(popup_window, TRUE);
    box(popup_window, 0, 0);
    mvwaddstr(popup_window, 0, 32, "Connection:" );

    mvwaddstr(popup_window, 5, 10, "join a new server:");
    mvwaddstr(popup_window, 5, 43, "or re-join a previous server:");

    refresh();


    print_border(popup_window);
    wrefresh(popup_window);

    connection_history_t history = get_connection_history();
    list_history(popup_window, &history);
    short history_pointer = -1;

    form_buffer_t input_buffer = create_buffer();

    char empty_buffer[18] = {0};
    memset(empty_buffer, ' ', sizeof(char) * 16);
    empty_buffer[17] = '\0';

    while(1){
        char key_pressed = getch();

        switch(key_pressed){
            case 0x09: /* TAB */
               
                break;
            case 0x07:{ /* Backspace ( actually the BELL ) */
                /* Update the buffer */
               pop_from_buffer(&input_buffer);

                /* Update the UI */
                mvwaddch(popup_window, 8, 10+input_buffer.size , ' ');
            }
                break;        
            case 0x0A: /* Enter ( actually the NL ) */
                goto CLEANING_UP;
            case 0x03: /* Arrow up */
                history_pointer = history_pointer == -1 ? 0 : ((history_pointer+1) % history.size) ;
                
                /* Update the buffer */
                copyn(&input_buffer, history.data[history_pointer], strlen(history.data[history_pointer]));
                
                /*Update the UI*/
                for(int i = 0; i < 18; i++){ mvwaddch(popup_window, 8,10+i, ' ');} // clear
                mvwaddstr(popup_window, 8, 10, input_buffer.buffer ); // overwrite

                break;
            case 0x02: /* Arrow down */
                history_pointer = history_pointer == -1 ? 0 : history_pointer-1;
                history_pointer = history_pointer == -1 ? 0 : history_pointer;


                /* Update the buffer */
                copyn(&input_buffer, history.data[history_pointer], strlen(history.data[history_pointer]));
                
                /*Update the UI*/
                for(int i = 0; i < 18; i++){ mvwaddch(popup_window, 8,10+i, ' ');} // clear
                mvwaddstr(popup_window, 8, 10, input_buffer.buffer );


                break;
            default:{

                /*Update the buffer*/
                append_to_buffer(&input_buffer, key_pressed);
              
                /* Update the UI */
                mvwaddstr(popup_window, 8, 10, input_buffer.buffer );
            }
        }
        wrefresh(popup_window);
    }
CLEANING_UP:
    /* Cleaning up */
    delwin(popup_window);
    endwin();
    refresh();

    free_buffer(&input_buffer);

    free_connection_history(&history);
}
