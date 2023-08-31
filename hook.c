#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#define DEF_PROC_NAME "WINWORD.exe"

HINSTANCE g_hInstance = NULL;
HHOOK g_hHook = NULL;
HWND g_hWnd = NULL;

BOOL WINAPI DllMain(HINSTANCE hinstDll, DWORD dwReason, LPVOID lpvReserved)
{
    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:
        g_hInstance = hinstDll;
        break;
    
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    char szPath[MAX_PATH] = {0,};
    char *p = NULL;

    if(nCode >= 0)
    {
        if(!(lParam & 0x80000000))
        {
            GetModuleFileNameA(NULL, szPath, MAX_PATH);
            p = strrchr(szPath, '\\');

            if(!_stricmp(p+1, DEF_PROC_NAME))
            {

                switch (wParam)
                {
                case 'A': case 'E': case 'I': case 'O': case 'U':
                    return 1;
                    break;
                case VK_SPACE:
                    MessageBoxW(NULL, L"cannot input space", L"Error", MB_OKCANCEL | MB_ICONEXCLAMATION);
                    return 1;
                    break;
                case VK_RETURN:
                    MessageBoxW(NULL, L"cannot input return", L"Error", MB_OKCANCEL | MB_ICONEXCLAMATION);
                    return 1;
                    break;
                default:
                    break;
                }
            }
        }
    }
    return CallNextHookEx(g_hHook, nCode, wParam, lParam);
}

#ifdef __cplusplus
extern "C" {
#endif

__declspec(dllexport) void Hookstart()
{
    g_hHook = SetWindowsHookExW(WH_KEYBOARD, KeyboardProc, g_hInstance, 0);
}

__declspec(dllexport) void Hookstop()
{
    if(g_hHook)
    {
        UnhookWindowsHookEx(g_hHook);
        g_hHook = NULL;
    }
}

#ifdef __cplusplus
}
#endif