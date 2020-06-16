// D3D11 - MAIN.CPP
#include "main.h"
#include "../sharedcode/Logging.h"
#include "../sharedcode/PluginLoader.h"

HMODULE originalD3D11 = NULL;
UINT64 p[51];

void loadOriginalD3D11()
{
    char dllpath[MAX_PATH];
    GetSystemDirectory(dllpath, MAX_PATH);
    strcat(dllpath, "\\d3d11.dll");
    originalD3D11 = LoadLibrary(dllpath);
    if(!originalD3D11)
        return;
    p[0] = (UINT64)GetProcAddress(originalD3D11, "CreateDirect3D11DeviceFromDXGIDevice");
    p[1] = (UINT64)GetProcAddress(originalD3D11, "CreateDirect3D11SurfaceFromDXGISurface");
    p[2] = (UINT64)GetProcAddress(originalD3D11, "D3D11CoreCreateDevice");
    p[3] = (UINT64)GetProcAddress(originalD3D11, "D3D11CoreCreateLayeredDevice");
    p[4] = (UINT64)GetProcAddress(originalD3D11, "D3D11CoreGetLayeredDeviceSize");
    p[5] = (UINT64)GetProcAddress(originalD3D11, "D3D11CoreRegisterLayers");
    p[6] = (UINT64)GetProcAddress(originalD3D11, "D3D11CreateDevice");
    p[7] = (UINT64)GetProcAddress(originalD3D11, "D3D11CreateDeviceAndSwapChain");
    p[8] = (UINT64)GetProcAddress(originalD3D11, "D3D11CreateDeviceForD3D12");
    p[9] = (UINT64)GetProcAddress(originalD3D11, "D3D11On12CreateDevice");
    p[10] = (UINT64)GetProcAddress(originalD3D11, "D3DKMTCloseAdapter");
    p[11] = (UINT64)GetProcAddress(originalD3D11, "D3DKMTCreateAllocation");
    p[12] = (UINT64)GetProcAddress(originalD3D11, "D3DKMTCreateContext");
    p[13] = (UINT64)GetProcAddress(originalD3D11, "D3DKMTCreateDevice");
    p[14] = (UINT64)GetProcAddress(originalD3D11, "D3DKMTCreateSynchronizationObject");
    p[15] = (UINT64)GetProcAddress(originalD3D11, "D3DKMTDestroyAllocation");
    p[16] = (UINT64)GetProcAddress(originalD3D11, "D3DKMTDestroyContext");
    p[17] = (UINT64)GetProcAddress(originalD3D11, "D3DKMTDestroyDevice");
    p[18] = (UINT64)GetProcAddress(originalD3D11, "D3DKMTDestroySynchronizationObject");
    p[19] = (UINT64)GetProcAddress(originalD3D11, "D3DKMTEscape");
    p[20] = (UINT64)GetProcAddress(originalD3D11, "D3DKMTGetContextSchedulingPriority");
    p[21] = (UINT64)GetProcAddress(originalD3D11, "D3DKMTGetDeviceState");
    p[22] = (UINT64)GetProcAddress(originalD3D11, "D3DKMTGetDisplayModeList");
    p[23] = (UINT64)GetProcAddress(originalD3D11, "D3DKMTGetMultisampleMethodList");
    p[24] = (UINT64)GetProcAddress(originalD3D11, "D3DKMTGetRuntimeData");
    p[25] = (UINT64)GetProcAddress(originalD3D11, "D3DKMTGetSharedPrimaryHandle");
    p[26] = (UINT64)GetProcAddress(originalD3D11, "D3DKMTLock");
    p[27] = (UINT64)GetProcAddress(originalD3D11, "D3DKMTOpenAdapterFromHdc");
    p[28] = (UINT64)GetProcAddress(originalD3D11, "D3DKMTOpenResource");
    p[29] = (UINT64)GetProcAddress(originalD3D11, "D3DKMTPresent");
    p[30] = (UINT64)GetProcAddress(originalD3D11, "D3DKMTQueryAdapterInfo");
    p[31] = (UINT64)GetProcAddress(originalD3D11, "D3DKMTQueryAllocationResidency");
    p[32] = (UINT64)GetProcAddress(originalD3D11, "D3DKMTQueryResourceInfo");
    p[33] = (UINT64)GetProcAddress(originalD3D11, "D3DKMTRender");
    p[34] = (UINT64)GetProcAddress(originalD3D11, "D3DKMTSetAllocationPriority");
    p[35] = (UINT64)GetProcAddress(originalD3D11, "D3DKMTSetContextSchedulingPriority");
    p[36] = (UINT64)GetProcAddress(originalD3D11, "D3DKMTSetDisplayMode");
    p[37] = (UINT64)GetProcAddress(originalD3D11, "D3DKMTSetDisplayPrivateDriverFormat");
    p[38] = (UINT64)GetProcAddress(originalD3D11, "D3DKMTSetGammaRamp");
    p[39] = (UINT64)GetProcAddress(originalD3D11, "D3DKMTSetVidPnSourceOwner");
    p[40] = (UINT64)GetProcAddress(originalD3D11, "D3DKMTSignalSynchronizationObject");
    p[41] = (UINT64)GetProcAddress(originalD3D11, "D3DKMTUnlock");
    p[42] = (UINT64)GetProcAddress(originalD3D11, "D3DKMTWaitForSynchronizationObject");
    p[43] = (UINT64)GetProcAddress(originalD3D11, "D3DKMTWaitForVerticalBlankEvent");
    p[44] = (UINT64)GetProcAddress(originalD3D11, "D3DPerformance_BeginEvent");
    p[45] = (UINT64)GetProcAddress(originalD3D11, "D3DPerformance_EndEvent");
    p[46] = (UINT64)GetProcAddress(originalD3D11, "D3DPerformance_GetStatus");
    p[47] = (UINT64)GetProcAddress(originalD3D11, "D3DPerformance_SetMarker");
    p[48] = (UINT64)GetProcAddress(originalD3D11, "EnableFeatureLevelUpgrade");
    p[49] = (UINT64)GetProcAddress(originalD3D11, "OpenAdapter10");
    p[50] = (UINT64)GetProcAddress(originalD3D11, "OpenAdapter10_2");
}

DWORD WINAPI Start(LPVOID lpParam)
{
    logStart("d3d11_proxy64.log");
    loadOriginalD3D11();
    if(!originalD3D11)
    {
        logprintf(">>Error loading original D3D11.DLL!\n");
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
            // attach to process
            // return FALSE to fail DLL load
            CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Start, 0, 0, 0);
            break;

        case DLL_PROCESS_DETACH:
            // detach from process
            if (originalD3D11)
                FreeLibrary(originalD3D11);
            break;

        case DLL_THREAD_ATTACH:
            // attach to thread
            break;

        case DLL_THREAD_DETACH:
            // detach from thread
            break;
    }
    return TRUE; // successful
}

extern "C" __declspec(dllexport) void CreateDirect3D11DeviceFromDXGIDevice()
{

    asm("jmp *p + 0 * 8\n\t");
}


extern "C" __declspec(dllexport) void CreateDirect3D11SurfaceFromDXGISurface()
{

    asm("jmp *p + 1 * 8\n\t");
}


extern "C" __declspec(dllexport) void D3D11CoreCreateDevice()
{

    asm("jmp *p + 2 * 8\n\t");
}


extern "C" __declspec(dllexport) void D3D11CoreCreateLayeredDevice()
{

    asm("jmp *p + 3 * 8\n\t");
}


extern "C" __declspec(dllexport) void D3D11CoreGetLayeredDeviceSize()
{

    asm("jmp *p + 4 * 8\n\t");
}


extern "C" __declspec(dllexport) void D3D11CoreRegisterLayers()
{

    asm("jmp *p + 5 * 8\n\t");
}


extern "C" __declspec(dllexport) void D3D11CreateDevice()
{

    asm("jmp *p + 6 * 8\n\t");
}


extern "C" __declspec(dllexport) void D3D11CreateDeviceAndSwapChain()
{

    asm("jmp *p + 7 * 8\n\t");
}


extern "C" __declspec(dllexport) void D3D11CreateDeviceForD3D12()
{

    asm("jmp *p + 8 * 8\n\t");
}


extern "C" __declspec(dllexport) void D3D11On12CreateDevice()
{

    asm("jmp *p + 9 * 8\n\t");
}


extern "C" __declspec(dllexport) void D3DKMTCloseAdapter()
{

    asm("jmp *p + 10 * 8\n\t");
}


extern "C" __declspec(dllexport) void D3DKMTCreateAllocation()
{

    asm("jmp *p + 11 * 8\n\t");
}


extern "C" __declspec(dllexport) void D3DKMTCreateContext()
{

    asm("jmp *p + 12 * 8\n\t");
}


extern "C" __declspec(dllexport) void D3DKMTCreateDevice()
{

    asm("jmp *p + 13 * 8\n\t");
}


extern "C" __declspec(dllexport) void D3DKMTCreateSynchronizationObject()
{

    asm("jmp *p + 14 * 8\n\t");
}


extern "C" __declspec(dllexport) void D3DKMTDestroyAllocation()
{

    asm("jmp *p + 15 * 8\n\t");
}


extern "C" __declspec(dllexport) void D3DKMTDestroyContext()
{

    asm("jmp *p + 16 * 8\n\t");
}


extern "C" __declspec(dllexport) void D3DKMTDestroyDevice()
{

    asm("jmp *p + 17 * 8\n\t");
}


extern "C" __declspec(dllexport) void D3DKMTDestroySynchronizationObject()
{

    asm("jmp *p + 18 * 8\n\t");
}


extern "C" __declspec(dllexport) void D3DKMTEscape()
{

    asm("jmp *p + 19 * 8\n\t");
}


extern "C" __declspec(dllexport) void D3DKMTGetContextSchedulingPriority()
{

    asm("jmp *p + 20 * 8\n\t");
}


extern "C" __declspec(dllexport) void D3DKMTGetDeviceState()
{

    asm("jmp *p + 21 * 8\n\t");
}


extern "C" __declspec(dllexport) void D3DKMTGetDisplayModeList()
{

    asm("jmp *p + 22 * 8\n\t");
}


extern "C" __declspec(dllexport) void D3DKMTGetMultisampleMethodList()
{

    asm("jmp *p + 23 * 8\n\t");
}


extern "C" __declspec(dllexport) void D3DKMTGetRuntimeData()
{

    asm("jmp *p + 24 * 8\n\t");
}


extern "C" __declspec(dllexport) void D3DKMTGetSharedPrimaryHandle()
{

    asm("jmp *p + 25 * 8\n\t");
}


extern "C" __declspec(dllexport) void D3DKMTLock()
{

    asm("jmp *p + 26 * 8\n\t");
}


extern "C" __declspec(dllexport) void D3DKMTOpenAdapterFromHdc()
{

    asm("jmp *p + 27 * 8\n\t");
}


extern "C" __declspec(dllexport) void D3DKMTOpenResource()
{

    asm("jmp *p + 28 * 8\n\t");
}


extern "C" __declspec(dllexport) void D3DKMTPresent()
{

    asm("jmp *p + 29 * 8\n\t");
}


extern "C" __declspec(dllexport) void D3DKMTQueryAdapterInfo()
{

    asm("jmp *p + 30 * 8\n\t");
}


extern "C" __declspec(dllexport) void D3DKMTQueryAllocationResidency()
{

    asm("jmp *p + 31 * 8\n\t");
}


extern "C" __declspec(dllexport) void D3DKMTQueryResourceInfo()
{

    asm("jmp *p + 32 * 8\n\t");
}


extern "C" __declspec(dllexport) void D3DKMTRender()
{

    asm("jmp *p + 33 * 8\n\t");
}


extern "C" __declspec(dllexport) void D3DKMTSetAllocationPriority()
{

    asm("jmp *p + 34 * 8\n\t");
}


extern "C" __declspec(dllexport) void D3DKMTSetContextSchedulingPriority()
{

    asm("jmp *p + 35 * 8\n\t");
}


extern "C" __declspec(dllexport) void D3DKMTSetDisplayMode()
{

    asm("jmp *p + 36 * 8\n\t");
}


extern "C" __declspec(dllexport) void D3DKMTSetDisplayPrivateDriverFormat()
{

    asm("jmp *p + 37 * 8\n\t");
}


extern "C" __declspec(dllexport) void D3DKMTSetGammaRamp()
{

    asm("jmp *p + 38 * 8\n\t");
}


extern "C" __declspec(dllexport) void D3DKMTSetVidPnSourceOwner()
{

    asm("jmp *p + 39 * 8\n\t");
}


extern "C" __declspec(dllexport) void D3DKMTSignalSynchronizationObject()
{

    asm("jmp *p + 40 * 8\n\t");
}


extern "C" __declspec(dllexport) void D3DKMTUnlock()
{

    asm("jmp *p + 41 * 8\n\t");
}


extern "C" __declspec(dllexport) void D3DKMTWaitForSynchronizationObject()
{

    asm("jmp *p + 42 * 8\n\t");
}


extern "C" __declspec(dllexport) void D3DKMTWaitForVerticalBlankEvent()
{

    asm("jmp *p + 43 * 8\n\t");
}


extern "C" __declspec(dllexport) void D3DPerformance_BeginEvent()
{

    asm("jmp *p + 44 * 8\n\t");
}


extern "C" __declspec(dllexport) void D3DPerformance_EndEvent()
{

    asm("jmp *p + 45 * 8\n\t");
}


extern "C" __declspec(dllexport) void D3DPerformance_GetStatus()
{

    asm("jmp *p + 46 * 8\n\t");
}


extern "C" __declspec(dllexport) void D3DPerformance_SetMarker()
{

    asm("jmp *p + 47 * 8\n\t");
}


extern "C" __declspec(dllexport) void EnableFeatureLevelUpgrade()
{

    asm("jmp *p + 48 * 8\n\t");
}


extern "C" __declspec(dllexport) void OpenAdapter10()
{

    asm("jmp *p + 49 * 8\n\t");
}


extern "C" __declspec(dllexport) void OpenAdapter10_2()
{

    asm("jmp *p + 50 * 8\n\t");
}
