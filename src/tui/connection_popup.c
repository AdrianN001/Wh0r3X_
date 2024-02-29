#include "../../lib/tui/connection_popup.h"
#include <string.h>


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
    /*
    for (int i = 0; i < history->size;i++){
        free(history->data[i]);
    }*/
    free(history->data);
}


void draw_border(WINDOW* popup_window){

    int x_center = (CONNECTION_POPUP_WINDOW_ROW + CONNECTION_POPUP_WINDOW_HEIGHT) / 1.8;

    for (int vertical = 2; vertical < 18; vertical++){
        mvwaddch(popup_window, vertical, x_center, '|'| A_BOLD );
        mvwaddch(popup_window, vertical, x_center+1, '|' | A_BOLD  );
    }
}

void list_history(WINDOW* window, connection_history_t* history ){

    if (history->size == 0|| 1){
        wattron(window, COLOR_PAIR(WARNING_COLOR_PAIR));

        mvwaddstr(window, 8 , 46, "Hmmm. It seems, that...");
        mvwaddstr(window, 10, 40, "you haven't been on an irc server");
        mvwaddstr(window, 12, 53, "before");
        wattroff(window, COLOR_PAIR(WARNING_COLOR_PAIR));
        wrefresh(window);
        return;
    }

    for(int i = 0; i < history->size; i++){
        mvwaddstr(window, 8+i, 52, history->data[i]);
    }
    wrefresh(window);
}


char* start_connection_popup_box(WINDOW *base_window){


    const int x_center = (CONNECTION_POPUP_WINDOW_COLS - CONNECTION_POPUP_WINDOW_WIDTH) / 2;
    const int y_center = (CONNECTION_POPUP_WINDOW_ROW - CONNECTION_POPUP_WINDOW_HEIGHT) / 2;

    WINDOW* popup_window = subwin(base_window, CONNECTION_POPUP_WINDOW_HEIGHT, CONNECTION_POPUP_WINDOW_WIDTH, y_center, x_center);    
    
    keypad(popup_window, TRUE);
    box(popup_window, 0, 0);
    mvwaddstr(popup_window, 0, 32, "Connection:" );

    wattron(popup_window, COLOR_PAIR(MAIN_COLOR_PAIR));
    mvwaddstr(popup_window, 5, 10, "join a new server:");
    mvwaddstr(popup_window, 5, 43, "or re-join a previous server:");
    wattroff(popup_window, COLOR_PAIR(MAIN_COLOR_PAIR));

    refresh();


    draw_border(popup_window);
    wrefresh(popup_window);

    connection_history_t history = get_connection_history();
    list_history(popup_window, &history);
    short history_pointer = -1;

    form_buffer_t input_buffer = create_buffer(22);


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
                history_pointer = history_pointer == -1 ? (history.size -1) : history_pointer;


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
    free_connection_history(&history);

    return input_buffer.buffer;

}
