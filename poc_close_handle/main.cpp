#include "common.hpp"

uint32_t get_process_id(const std::wstring& processName)
{
    PROCESSENTRY32 process_information;
    process_information.dwSize = sizeof(process_information);

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    
    if (snapshot != INVALID_HANDLE_VALUE)
    {
        Process32First(snapshot, &process_information);
        
        if (!processName.compare(process_information.szExeFile))
        {
            CloseHandle(snapshot);
            return process_information.th32ProcessID;
        }

        while (Process32Next(snapshot, &process_information))
        {
            if (!processName.compare(process_information.szExeFile))
            {
                CloseHandle(snapshot);
                return process_information.th32ProcessID;
            }
        }
    }

    CloseHandle(snapshot);
    return 0;
}

int main(void)
{
    std::cout << "[+] loader started..." << std::endl;

    const auto target_pid = get_process_id(L"poc_close_handle_victim.exe");
    
    if (!target_pid)
    {
        std::cout << "[+] couldn't get the target process' pid, press a button to exit.";
        std::cin.get();
        return 1;
    }

    std::cout << "[+] pid is " << std::dec << target_pid << std::endl;

    std::cout << "[+] grabbing kernel32.dll module handle" << std::endl;

    auto kernel_32 = GetModuleHandle(L"kernel32.dll");

    if (!kernel_32)
    {
        // LoadLibrary returns the modules' handle after loading
        kernel_32 = LoadLibrary(L"kernel32.dll");
    }

    std::cout << "[+] kernel32.dll module handle found: " << std::hex << kernel_32 << std::endl;
    
    // windows processes share certain physical memory regions until they're edited, this means our
    // virtual address will also be valid in the other process' context, since kernel32.dll gets loaded
    // for every process and its .text section gets rarely modified by regular software, windows uses
    // a technique called CoW (copy-on-write) to only allocate a section again in the current process
    // if it's edited.
    const auto load_library_address = GetProcAddress(kernel_32, "LoadLibraryA");

    std::cout << "[+] LoadLibraryA address: " << std::hex << load_library_address << std::endl;

    std::cout << "[+] opening an handle to the target process..." << std::endl;

    const auto process_handle = OpenProcess(PROCESS_ALL_ACCESS, false, target_pid);

    if (!process_handle)
    {
        std::cout << "[+] couldn't get an handle to the target process, press a button to exit." << std::endl;
        std::cin.get();
        return 1;
    }
    else
    {
        std::cout << "[+] handle opened: " << std::hex << process_handle << std::endl;
    }


    // get full path to pass as parameter to the LoadLibraryA function (since we're using LoadLibrary's ANSI version let's
    // make sure we use the ANSI version of GetFullPathName too).
    char full_path[1024];
    GetFullPathNameA("poc_close_handle_module.dll", sizeof(full_path), full_path, nullptr);

    // allocate the space in the target process 
    const auto argument = VirtualAllocEx(process_handle, nullptr, sizeof(full_path), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    
    // write the argument in the process' memory (although we could just use full_path instead of &full_path[0]
    // since arrays decay in pointers when used as arguments in cpp, for clarity we'll use &full_path[0]).
    WriteProcessMemory(process_handle, argument, full_path, strlen(full_path), nullptr);

    // start the LoadLibraryA function in a new thread
    CreateRemoteThread(process_handle, nullptr, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(load_library_address), argument, NULL, nullptr);

    std::cout << "[+] library loaded, freeing system resources in 5 seconds and exiting." << std::endl;

    // standby for a few seconds
    std::this_thread::sleep_for(5s);

    // free the resources
    std::cout << "[+] freeing system resources..." << std::endl;

    // do NOT pass MEM_RELEASE | MEM_DECOMMIT to VirtualFreeEx, the call *will* fail
    VirtualFreeEx(process_handle, argument, NULL, MEM_RELEASE);
    CloseHandle(process_handle);
    
    return 0;
}