#include "../../lib/config/init.h"

#ifndef assert
#define assert(x) if((!(x))){printf("assertion error!\n error at %s() function\n",__func__); exit(1);}
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

bool try_create_config_directory(){

    char path_buffer[32] = {0};
    sprintf(path_buffer, "~/%s", CONFIG_DIR_NAME);
    struct stat st = {0};

    if (stat(path_buffer, &st) == -1) {
        mkdir(path_buffer, 0700);
        return false;
    }
    return true;
}

bool try_create_server_history(){
    char path_buffer[32] = {0};
    sprintf(path_buffer, "~/%s/%s", CONFIG_DIR_NAME, SERVER_HIS_NAME);

    struct stat st = {0};
    if (stat(path_buffer, &st) == -1) {
        FILE* fp = fopen(path_buffer, "a");
        fclose(fp);
        return false;
    }
    return true;
}