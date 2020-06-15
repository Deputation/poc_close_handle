# CloseHandle hooking proof-of-concept.

Everything in this repository is released under the GPLv3 License.

This repository contains three projects: poc_close_handle_module, poc_close_handle_loader, poc_close_handle_victim. The first is the module, the core functionality of the project, the second is a simple CreateRemoteThread dynamic linked library loader, while the third is a simple victim / target / dummy application that loads the library on its own to demonstrate its functionality. 

This project demonstrates the possibility to hook CloseHandle, a function in kernel32.dll. By hooking such a function we have the ability to use every handle used by the target/victim application before it's closed. Everything in this repository is here for educational purposes and i do not condone its use for any other reason, the project was written in 30 minutes on a sunday, so take its code with a grain of salt and feel free to open pull requests.

The repository DOES NOT include the MinHook hooking library. You're meant to add it yourself, Debug or x86 configurations are not available. This is for the sole purpose of stopping kids from abusing of the code in this repository. 

I decline any liability & warranty regarding this project. I am not to be held liable for anything anyone might use anything that can be found in this repository for. For more information, reead the GPLv3 License, provided in the file named "LICENSE" inside the repository.
