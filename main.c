#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "conio.h"

#define DEF_DLL_NAME L"hook.dll"
#define DEF_HOOKSTART "Hookstart"
#define DEF_HOOKSTOP "Hookstop"

typedef void (*PFN_HOOKSTART)();
typedef void (*PFN_HOOKSTOP)();

int main()
{
    HMODULE hDll;
    PFN_HOOKSTART Hookstart;
    PFN_HOOKSTOP Hookstop;

    hDll = LoadLibraryW(DEF_DLL_NAME);
    if(!hDll)
    {
        printf("failed to load library\n");
        system("PAUSE");
        exit(0);
    }
    Hookstart = GetProcAddress(hDll, DEF_HOOKSTART);
    Hookstop = GetProcAddress(hDll, DEF_HOOKSTOP);

    Hookstart();

    printf("press q to quit\n");
    while(_getch() != 'q');
    
    Hookstop();

    FreeLibrary(hDll);
    return 0;
}