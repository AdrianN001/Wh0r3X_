#pragma once
#include "user.h"

bool group_incomming_message(struct user* session_user, char* response_buffer);
char* try_format_response(struct user* session_user, char* response_buffer, char* out);
int check_for_ping(char* response_buffer, char* ping_buffer);
