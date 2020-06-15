#include "common.hpp"

DWORD WINAPI start(HMODULE hModule)
{
    // allocate console
    AllocConsole();

    // redirect cout
    freopen("CONOUT$", "w", stdout);

    // initialize the hooking library
    MH_Initialize();
    
    // load kernel32.dll handle
    auto kernel_32 = GetModuleHandle(L"kernel32.dll");

    // load the library if the handle to it is 0
    if (!kernel_32)
    {
        kernel_32 = LoadLibrary(L"kernel32.dll");
    }

    // get CloseHandle's virtual address
    auto close_handle = GetProcAddress(kernel_32, "CloseHandle");

    // if the address has been found
    if (close_handle)
    {
        MH_CreateHook(close_handle, &hook::close_handle_hook, reinterpret_cast<void**>(&hook::close_handle_original));
        MH_EnableHook(close_handle);
    }

    return 0;
}

DWORD WINAPI stop(HMODULE hModule)
{
    MH_DisableHook(MH_ALL_HOOKS);
    MH_Uninitialize();
    FreeLibraryAndExitThread(hModule, 0);
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CloseHandle(CreateThread(nullptr, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(start), hModule, NULL, nullptr));
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        CloseHandle(CreateThread(nullptr, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(stop), hModule, NULL, nullptr));
        break;
    }
    return TRUE;
}

