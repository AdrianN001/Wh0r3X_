#pragma once
#include "user.h"

char* try_format_response(struct user* session_user, char* response_buffer, char* out);
int check_for_ping(char* response_buffer, char* ping_buffer);
int format_and_group_incomming_messages(struct user* session_user, char* temp_buffer);