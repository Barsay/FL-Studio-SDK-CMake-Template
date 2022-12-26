#ifndef FL_STUDIO_SDK_CMAKE_TEMPLATE_PLUGIN_H
#define FL_STUDIO_SDK_CMAKE_TEMPLATE_PLUGIN_H

//Header files included for the SDK
#include "fp_plugclass.h"
#include "fp_cplug.h"
#include "generictransport.h"

//header file, automatically configurated by CMake.
#include "definitions.h"

const int NumParamsConst = 1;    // the amount of parameters
const int StateSizeConst = NumParamsConst * sizeof(int);  // the size of all parameters together

// Information structure describing this plugin to the host
TFruityPlugInfo PlugInfo = {
        CurrentSDKVersion,
        PLUGIN_NAME,
        "PLUG",
        // Set plugin type.
        FPF_Type_Effect,
        NumParamsConst,
        // infinite polyphony (it's an effect plugin)
        0,
        // one internal controller
        1
};

//Minimal Example Plugin class.
class Plugin : public TCPPFruityPlug {

public:
    int ParamValue[NumParamsConst];
    //constructor
    Plugin(int Tag, TFruityPlugHost *Host);
    //inherited functions
    virtual void _stdcall DestroyObject();
    virtual int _stdcall Dispatcher(int ID, int Index, int Value);
    virtual void _stdcall Idle();
    virtual void _stdcall SaveRestoreState(IStream *Stream, BOOL Save);
    virtual void _stdcall GetName(int Section, int Index, int Value, char *Name);
    virtual int _stdcall ProcessParam(int Index, int Value, int RECFlags);
    virtual void _stdcall Eff_Render(PWAV32FS SourceBuffer, PWAV32FS DestBuffer, int Length);

    void ResetParams();

};

#endif //FL_STUDIO_SDK_CMAKE_TEMPLATE_PLUGIN_H
