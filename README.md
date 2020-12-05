
# poc_close_handle: hooking the CloseHandle function in trusted, signed applications to steal process handles.

Everything in this repository is released under the MIT license.

I AM NOT TO BE HELD RESPONSIBLE FOR ANY SORT OF USAGE REGARDING ANYTHING IN THIS REPOSITORY. 

This repository contains three projects: poc_close_handle_module, poc_close_handle_loader, poc_close_handle_victim. The first is the module, the core functionality of the project, the second is a simple CreateRemoteThread dynamic linked library loader, while the third is a simple victim / target / dummy application that loads the library on its own to demonstrate its functionality. 

This project demonstrates the possibility to hook CloseHandle, a function in kernel32.dll. By hooking such a function we have the ability to use every handle used by the target/victim application before it's closed, this way, this proof-of-concept makes it potentially possible to gather a handle to access a process protected by commercial anti-cheating solutions. Some other minor edits may be needed to get it to work as well. This is by design. Do not abuse this project. :)

Everything in this repository is here for educational purposes and i do not condone its use for any other reason, the project was written in 30 minutes on a sunday, so take its code with a grain of salt and feel free to open pull requests.

This repository DOES NOT include the MinHook hooking library. You're meant to add it yourself, Debug or x86 configurations are not available. This is for the sole purpose of stopping people from abusing the code in this repository by limiting its functionalities.
