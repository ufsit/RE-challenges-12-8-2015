int main(int argc, char * argv[]){
    puts("This challenge has been solved!");
    puts("All you had to do was call main.");
}

void real_start(){
    asm (   "push   $0xa;"
            "push   $0x21646c72;"
            "push   $0x6f77206f;"
            "push   $0x6c6c6568;"
            "mov    $0xd, %edx;"
            "mov    %esp, %ecx;"
            "mov    $0x1, %ebx;"
            "mov    $0x4, %eax;"
            "int    $0x80;"
            "mov    $0x1, %eax;"
            "int    $0x80;"
        );
}
