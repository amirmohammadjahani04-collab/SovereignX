typedef unsigned long long EFI_STATUS;
typedef void* EFI_HANDLE;
typedef void* EFI_SYSTEM_TABLE;


EFI_STATUS efi_main(
    EFI_HANDLE ImageHandle,
    EFI_SYSTEM_TABLE *SystemTable
)
{

    volatile unsigned long long *framebuffer;

    while(1)
    {
        /*
          bakOS UEFI Loader
          مرحله بعد:
          پیدا کردن Kernel
        */
    }

    return 0;
}
