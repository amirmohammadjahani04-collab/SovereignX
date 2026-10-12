void kernel_main()
{
    volatile char *video =
        (char*)0xb8000;

    video[0] = 'b';
    video[1] = 0x07;

    video[2] = 'a';
    video[3] = 0x07;

    video[4] = 'k';
    video[5] = 0x07;


    while(1)
    {
    }
}
