#include <Windows.h>
#include <stdio.h>

#include "fp_cplug.h"
#include "testplug.h"



// This function allows FL to load an instance of the plugin.
// It should be exported from the dll (usually through a module definition file (.def)
extern "C" TFruityPlug* _stdcall CreatePlugInstance(TFruityPlugHost *Host, int Tag)
{
	// example: check FL Studio version (not necessary in most plugins)
	if (Host->HostVersion < 006000000)
	{
		// format error buffer
		char error_buf[256];
		sprintf_s(error_buf, 256, "Saw VC|Error: FL Studio 6 or newer is required. (Current Version Id: %d)", Host->HostVersion);
		// example: show error message box through FL
		Host->Dispatcher(Tag, FHD_MsgBox, (intptr_t)error_buf, MB_OK | MB_ICONERROR);

		// return null
		return NULL;
	}

	// create the plugin object and return the pointer
	return new TTestPlug(Tag, Host, HInstance);
}



BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{

	switch (ul_reason_for_call)
	{
		// dll load library
		case DLL_PROCESS_ATTACH:
			HInstance = (HINSTANCE)hModule;		// save global instance handle. HInstance is defined in fp_plugclass.cpp
			break;

		// dll end library
		case DLL_PROCESS_DETACH:
			break;
	}

	return TRUE;
}
