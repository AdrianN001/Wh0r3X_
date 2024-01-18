#include <stdio.h>
#include "../src/user.c"

#define assert(x) if((!(x))){printf("assertion error!\n error at %s() function\n",__func__); exit(1);}

void test_registration_commands(){

    char* command_result = generate_username_command("username", "real name");
    assert(20 == 33);
}

void test_registration_process(){
    

    struct user new_user = {0};
    init_user(&new_user, "random_nickname", "nick name", "real name");
    connect_to_server(&new_user, "irc.w3.org", 6667);

}


int main(void){
    printf("hello world!");
    test_registration_process();

    return 0;
}