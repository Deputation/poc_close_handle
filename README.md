
# CloseHandle hooking proof-of-concept.

Everything in this repository is released under the MIT license.

I AM NOT TO BE HELD RESPONSIBLE FOR ANY SORT OF USAGE OF ANYTHING IN THIS REPOSITORY. 
I.E. do not come to me for anything regarding this.

This repository contains three projects: poc_close_handle_module, poc_close_handle_loader, poc_close_handle_victim. The first is the module, the core functionality of the project, the second is a simple CreateRemoteThread dynamic linked library loader, while the third is a simple victim / target / dummy application that loads the library on its own to demonstrate its functionality. 

This project demonstrates the possibility to hook CloseHandle, a function in kernel32.dll. By hooking such a function we have the ability to use every handle used by the target/victim application before it's closed. Everything in this repository is here for educational purposes and i do not condone its use for any other reason, the project was written in 30 minutes on a sunday, so take its code with a grain of salt and feel free to open pull requests.

This repository DOES NOT include the MinHook hooking library. You're meant to add it yourself, Debug or x86 configurations are not available. This is for the sole purpose of stopping people from abusing the code in this repository by limiting its functionalities. The project is not designed to be used in any sort of software, it's just a proof of concept, therefore is not readily usable for anything else than demonstrating the re-usability of handles before they're closed.

I decline any liability & do not offer any warranty regarding this project. I am not to be held liable for anything anyone might use anything that can be found in this repository for. For more information read the MIT License, provided in the file named "LICENSE" inside the repository.
