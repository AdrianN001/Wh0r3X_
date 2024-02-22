#include "../lib/exit_signal_hander.h"

static void exit_signal_handler(int signo){

    endwin();
    free_login_result(&result);
    
    free_complex_buffer(&history_buffer);
    leave_server_as_user(&session_user);
    exit(1);
}
