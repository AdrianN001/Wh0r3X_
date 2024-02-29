#pragma once
#include <stdbool.h>

#ifndef CONFIG_FILE_NAMES
#define CONFIG_FILE_NAMES

#define CONFIG_DIR_NAME ".wh0r3x"
#define SERVER_HIS_NAME ".history"

#endif

// Returns true if it has been already created
bool try_create_config_directory();
// Returns true if it has been already created
bool try_create_server_history();