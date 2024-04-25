#include "whorex/config/init.h"
#include "whorex/assert.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

bool try_create_config_directory(){

    char path_buffer[32] = {0};
    sprintf(path_buffer, "~/%s", config_dir_name);
    struct stat st = {0};

    if (stat(path_buffer, &st) == -1) {
        mkdir(path_buffer, 0700);
        return false;
    }
    return true;
}

bool try_create_server_history(){
    char path_buffer[32] = {0};
    sprintf(path_buffer, "~/%s/%s", config_dir_name, server_history_name);

    struct stat st = {0};
    if (stat(path_buffer, &st) == -1) {
        FILE* fp = fopen(path_buffer, "a");
        fclose(fp);
        return false;
    }
    return true;
}