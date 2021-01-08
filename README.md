
# poc_close_handle

## Hooking the CloseHandle function in trusted, signed applications to steal process handles.

## Code
Everything in this repository is released under the MIT license.

## Project structure
This repository contains three projects: poc_close_handle_module, poc_close_handle_loader, poc_close_handle_victim. The first is the module, the core functionality of the project, the second is a simple CreateRemoteThread dynamic linked library loader, while the third is a simple victim / target / dummy application that loads the library on its own to demonstrate its functionality. 

## PoC
This project demonstrates the possibility to hook CloseHandle, a function in kernel32.dll. By hooking such a function we have the ability to use every handle used by the target/victim application before it's closed, this way, this proof-of-concept makes it possible to gather a handle to access a process protected by commercial anti-cheating solutions. Some other minor edits may be needed to get it to work as well, like making sure the handle that you got is for a process, storing handles is also somethign that needs done so it's possible to not slow down the function while it's being called by the host process. This is by design to prevent abuse for ethical reasons, as I do not want any game's / program's integrity to be violated with this.

## Why?
Everything in this repository is here for educational purposes and i do not condone its use for any other reason.

## Info
This repository DOES NOT include the MinHook hooking library. You're meant to add it yourself, Debug or x86 configurations are not available. This is for the sole purpose of stopping people from abusing the code in this repository by limiting its functionalities & usability if not used by someone who knows what he/she/they are doing.
