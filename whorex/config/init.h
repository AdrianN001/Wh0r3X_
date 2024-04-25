#pragma once
#include <stdbool.h>

static const char* config_dir_name = ".whor3x";
static const char* server_history_name = ".history";



// Returns true if it has been already created
bool try_create_config_directory();
// Returns true if it has been already created
bool try_create_server_history();