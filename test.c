
void main()
{

    asm volatile(
        "mov $1, %rax\n"
        "syscall\n"
    );


    while(1);

}

