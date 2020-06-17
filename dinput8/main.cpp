// DINPUT8 - MAIN.CPP
#include "main.h"
#include "../sharedcode/Logging.h"
#include "../sharedcode/PluginLoader.h"

HMODULE originalDINPUT8 = NULL;
UINT64 p[1];

void loadOriginalDINPUT8()
{
    char dllpath[MAX_PATH];
    GetSystemDirectory(dllpath, MAX_PATH);
    strcat(dllpath, "\\dinput8.dll");
    originalDINPUT8 = LoadLibrary(dllpath);
    if(!originalDINPUT8)
        return;
    p[0] = (UINT64)GetProcAddress(originalDINPUT8, "DirectInput8Create");
}

DWORD WINAPI Start(LPVOID lpParam)
{
    logStart("dinput8_proxy64.log");
    loadOriginalDINPUT8();
    if(!originalDINPUT8)
    {
        logprintf(">>Error loading original DINPUT8.DLL!\n");
        logEnd();
        return 0;
    }
    loadPlugins("ASI");
    if(GetPluginLoadCount() == 0)
        loadPlugins(".");
    logEnd();
    return 0;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Start, 0, 0, 0);
            break;
        case DLL_PROCESS_DETACH:
            if (originalDINPUT8)
                FreeLibrary(originalDINPUT8);
            break;
    }
    return TRUE;
}

extern "C" __declspec(dllexport) void DirectInput8Create()
{
    asm("jmp *p\n\t");
}

