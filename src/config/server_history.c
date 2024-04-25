#include "whorex/config.h"
#include "whorex/assert.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void append_to_server_history(char* new_server){
    char path_buffer[32] = {0};
    sprintf(path_buffer, "~/%s/%s", config_dir_name, server_history_name);
    struct stat st = {0};
    assert(stat(path_buffer, &st) != -1);
    FILE* history_file = fopen(path_buffer, "a");
    fprintf(history_file, new_server);
    fclose(history_file);
}

// Caller has the responsibility
char** fetch_last_n_last_server(int n){
    char** main_buffer = (char**)malloc(sizeof(char*) * n);
    
}