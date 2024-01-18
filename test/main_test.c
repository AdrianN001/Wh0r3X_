#include <stdio.h>
#include "../src/user.c"
#include "../src/tui/form_buffer.c"

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

void test_form_buffer(){
    form_buffer_t nickname_buffer = create_buffer();
    append_to_buffer(&nickname_buffer, 'a');
    append_to_buffer(&nickname_buffer, 'b');
    append_to_buffer(&nickname_buffer, 'c');
    print(&nickname_buffer);

    pop_from_buffer(&nickname_buffer);
    pop_from_buffer(&nickname_buffer);

    append_to_buffer(&nickname_buffer, 's');
    append_to_buffer(&nickname_buffer, '2');
    append_to_buffer(&nickname_buffer, '4');
    append_to_buffer(&nickname_buffer, 'h');

    print(&nickname_buffer);

    char output[32] = {0};
    extract(&nickname_buffer, output);
    printf("%s -> %d\n", output, strlen(output));



    free_buffer(&nickname_buffer);


}

int main(void){
    printf("running test!\n");
    test_form_buffer();

    return 0;
}