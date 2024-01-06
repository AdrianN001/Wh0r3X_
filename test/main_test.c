#include <stdio.h>
#include "../user.c"

#define assert(x) if((!(x))){printf("assertion error!\n error at %s() function\n",__func__); exit(1);}

void test_registration_commands(){

    char* command_result = generate_username_command("username", "real name");
    printf("res %s\n", command_result);
    assert(20 == 33);
}

void test_registration_process(){

    struct user new_user = {0};
    init_user(&new_user, "NICKNAME", "USERNAME", "REALNAME");
    connect_to_server(&new_user, "127.0.0.1", 6667);
    free_user(&new_user);

}

int main(void){
    
    test_registration_process();

    return 0;
}