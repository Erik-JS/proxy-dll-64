// D3D12 - MAIN.CPP
#include "main.h"
#include "../sharedcode/Logging.h"
#include "../sharedcode/PluginLoader.h"

HMODULE originalD3D12 = NULL;
UINT64 p[51];

void loadOriginalD3D12()
{
    char dllpath[MAX_PATH];
    GetSystemDirectory(dllpath, MAX_PATH);
    strcat(dllpath, "\\d3d12.dll");
    originalD3D12 = LoadLibrary(dllpath);
    if(!originalD3D12)
        return;
    p[0] = (UINT64)GetProcAddress(originalD3D12, "D3D12CoreCreateLayeredDevice");
    p[1] = (UINT64)GetProcAddress(originalD3D12, "D3D12CoreGetLayeredDeviceSize");
    p[2] = (UINT64)GetProcAddress(originalD3D12, "D3D12CoreRegisterLayers");
    p[3] = (UINT64)GetProcAddress(originalD3D12, "D3D12CreateDevice");
    p[4] = (UINT64)GetProcAddress(originalD3D12, "D3D12CreateRootSignatureDeserializer");
    p[5] = (UINT64)GetProcAddress(originalD3D12, "D3D12CreateVersionedRootSignatureDeserializer");
    p[6] = (UINT64)GetProcAddress(originalD3D12, "D3D12DeviceRemovedExtendedData");
    p[7] = (UINT64)GetProcAddress(originalD3D12, "D3D12EnableExperimentalFeatures");
    p[8] = (UINT64)GetProcAddress(originalD3D12, "D3D12GetDebugInterface");
    p[9] = (UINT64)GetProcAddress(originalD3D12, "D3D12GetInterface");
    p[10] = (UINT64)GetProcAddress(originalD3D12, "D3D12PIXEventsReplaceBlock");
    p[11] = (UINT64)GetProcAddress(originalD3D12, "D3D12PIXGetThreadInfo");
    p[12] = (UINT64)GetProcAddress(originalD3D12, "D3D12PIXNotifyWakeFromFenceSignal");
    p[13] = (UINT64)GetProcAddress(originalD3D12, "D3D12PIXReportCounter");
    p[14] = (UINT64)GetProcAddress(originalD3D12, "D3D12SerializeRootSignature");
    p[15] = (UINT64)GetProcAddress(originalD3D12, "D3D12SerializeVersionedRootSignature");
    p[16] = (UINT64)GetProcAddress(originalD3D12, "GetBehaviorValue");
    p[17] = (UINT64)GetProcAddress(originalD3D12, "SetAppCompatStringPointer");
}

DWORD WINAPI Start(LPVOID lpParam)
{
    logStart("d3d12_proxy64.log");
    loadOriginalD3D12();
    if(!originalD3D12)
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
            CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Start, 0, 0, 0);
            break;
        case DLL_PROCESS_DETACH:
            if (originalD3D12)
                FreeLibrary(originalD3D12);
            break;
    }
    return TRUE;
}

extern "C" __declspec(dllexport) void D3D12CoreCreateLayeredDevice()
{
    asm("jmp *p + 0 * 8");
}


extern "C" __declspec(dllexport) void D3D12CoreGetLayeredDeviceSize()
{
    asm("jmp *p + 1 * 8");
}


extern "C" __declspec(dllexport) void D3D12CoreRegisterLayers()
{
    asm("jmp *p + 2 * 8");
}


extern "C" __declspec(dllexport) void D3D12CreateDevice()
{
    asm("jmp *p + 3 * 8");
}


extern "C" __declspec(dllexport) void D3D12CreateRootSignatureDeserializer()
{
    asm("jmp *p + 4 * 8");
}


extern "C" __declspec(dllexport) void D3D12CreateVersionedRootSignatureDeserializer()
{
    asm("jmp *p + 5 * 8");
}


extern "C" __declspec(dllexport) void D3D12DeviceRemovedExtendedData()
{
    asm("jmp *p + 6 * 8");
}


extern "C" __declspec(dllexport) void D3D12EnableExperimentalFeatures()
{
    asm("jmp *p + 7 * 8");
}


extern "C" __declspec(dllexport) void D3D12GetDebugInterface()
{
    asm("jmp *p + 8 * 8");
}


extern "C" __declspec(dllexport) void D3D12GetInterface()
{
    asm("jmp *p + 9 * 8");
}


extern "C" __declspec(dllexport) void D3D12PIXEventsReplaceBlock()
{
    asm("jmp *p + 10 * 8");
}


extern "C" __declspec(dllexport) void D3D12PIXGetThreadInfo()
{
    asm("jmp *p + 11 * 8");
}


extern "C" __declspec(dllexport) void D3D12PIXNotifyWakeFromFenceSignal()
{
    asm("jmp *p + 12 * 8");
}


extern "C" __declspec(dllexport) void D3D12PIXReportCounter()
{
    asm("jmp *p + 13 * 8");
}


extern "C" __declspec(dllexport) void D3D12SerializeRootSignature()
{
    asm("jmp *p + 14 * 8");
}


extern "C" __declspec(dllexport) void D3D12SerializeVersionedRootSignature()
{
    asm("jmp *p + 15 * 8");
}


extern "C" __declspec(dllexport) void GetBehaviorValue()
{
    asm("jmp *p + 16 * 8");
}


extern "C" __declspec(dllexport) void SetAppCompatStringPointer()
{
    asm("jmp *p + 17 * 8");
}
