#include "common.hpp"

int main(void) 
{
	LoadLibrary(L"poc_close_handle_module.dll");

	// wait for hook placement (very rudimental)
	std::this_thread::sleep_for(1s);

	while (true)
	{
		static int i = 0;

		// just call close handle to show the argument on the dll's console
		try
		{
			CloseHandle(reinterpret_cast<HANDLE>(i));
		}
		catch (std::exception e)
		{
			// catch it so the debugger doesn't freak out
		}
		
		i++;

		std::this_thread::sleep_for(1s);
	}
}