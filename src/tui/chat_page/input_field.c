#include "../../../lib/tui/chat_page.h"


void update_input_box(WINDOW* window, char new_character, form_buffer_t* buffer){
    
    switch((int)new_character){
        case 0x07:{ /* Backspace ( actually the BELL ) */

            pop_from_buffer(buffer); // Update the state

            mvwaddch(window, 2, 2+buffer->size +1, ' '); // Update the UI
            mvwaddch(window,2, 2+buffer->size  ,'_' | A_BLINK);

        }
            break;
        case 0x0A: /* Enter ( actually the NL ) */
            exit(1);
            break;
        default:{
            append_to_buffer(buffer, new_character);
            mvwaddstr(window, 2, 2, buffer->buffer); // Update the UI
            mvwaddch(window, 2, 2+buffer->size, '_' | A_BLINK);

            break;
        }
    }

    char percentage_buffer[7] = {0};
    const int percentage_of_buffer_filled = (int)(((float)buffer->size / (float)buffer->max_size ) * 100);
    sprintf(percentage_buffer, "  %d%%", percentage_of_buffer_filled);

    char exact[10] = {0};
    sprintf(exact, "  %d/%d", buffer->size, buffer->max_size);

    if (percentage_of_buffer_filled == 100){
        wattron(window, COLOR_PAIR(5));
    }

    mvwaddstr(window, 3, INPUT_FIELD_BOX_WINDOW_WIDTH - (strlen(exact) + 1), exact);
    mvwaddstr(window, 1, INPUT_FIELD_BOX_WINDOW_WIDTH - (strlen(percentage_buffer) +1), percentage_buffer);
    if (percentage_of_buffer_filled == 100){
        wattroff(window, COLOR_PAIR(5));
        wrefresh(window);
    }
}

WINDOW* start_input_field_box(WINDOW* base_window){
    WINDOW* popup_window;

    const int x_center = (INPUT_FIELD_BOX_WINDOW_COLS - INPUT_FIELD_BOX_WINDOW_WIDTH) / 2;
    const int y_center = (INPUT_FIELD_BOX_WINDOW_ROW - INPUT_FIELD_BOX_WINDOW_HEIGHT) / 2;

    popup_window = subwin(base_window, INPUT_FIELD_BOX_WINDOW_HEIGHT, INPUT_FIELD_BOX_WINDOW_WIDTH, y_center, x_center);

    assert(popup_window != NULL)




    keypad(popup_window, TRUE);
    box(popup_window, 0,0);

    refresh();
    wrefresh(popup_window);

    return popup_window;
}