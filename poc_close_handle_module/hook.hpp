#pragma once

namespace hook
{
    using close_handle_fn_t = BOOL(WINAPI*)(HANDLE object_handle);
    close_handle_fn_t close_handle_original = nullptr;

    BOOL close_handle_hook(HANDLE object_handle)
    {
        // we have a handle
        std::cout << "[+] a handle is being closed: " << std::hex << object_handle << std::endl;

        return close_handle_original(object_handle);
    }
}
