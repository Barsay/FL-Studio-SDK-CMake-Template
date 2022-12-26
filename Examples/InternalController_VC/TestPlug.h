//---------------------------------------------------------------------------
#ifndef TestPlugH
#define TestPlugH

#include "StdAfx.h"

#include "fp_plugclass.h"
#include "fp_cplug.h"

const int NumParamsConst = 1;    // the amount of parameters
const int StateSizeConst = NumParamsConst * sizeof(int);  // the size of all parameters together

class TTestPlug : public TCPPFruityPlug {
private:
    CDialog* EditorForm;
public:
    int ParamValue[NumParamsConst];

    TTestPlug(int Tag, TFruityPlugHost *Host);

    virtual void _stdcall DestroyObject();

    virtual int _stdcall Dispatcher(int ID, int Index, int Value);
    virtual void _stdcall Idle();
    virtual void _stdcall SaveRestoreState(IStream *Stream, BOOL Save);
    virtual void _stdcall GetName(int Section, int Index, int Value, char *Name);
    virtual int _stdcall ProcessParam(int Index, int Value, int RECFlags);
    virtual void _stdcall Eff_Render(PWAV32FS SourceBuffer, PWAV32FS DestBuffer, int Length);
};


//---------------------------------------------------------------------------
#endif
