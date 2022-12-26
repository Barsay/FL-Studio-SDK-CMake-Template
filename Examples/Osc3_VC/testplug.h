#ifndef TESTPLUG_H
#define TESTPLUG_H


#include <afxcoll.h>

#include "fp_def.h"
#include "fp_cplug.h"


// params
const int NumParamsConst = 3*4-1;

enum {
    pOsc1Level    = -1,
    pOsc1Shape    = 0,
    pOsc1Coarse   = 1,
    pOsc1Fine     = 2,
    pOsc2Level    = 3,
	pOsc2Shape	  = 4,
	pOsc2Coarse   = 5,
	pOsc2Fine     = 6,
    pOsc3Level    = 7,
	pOsc3Shape    = 8,
	pOsc3Coarse   = 9,
	pOsc3Fine     = 10
};


#define StateSize NumParamsConst*4  // params + switches
#define nOsc 3

struct TOsc {
    PWaveT ShapeP;
    int Pitch;
    float Level;
};

class TTestPlug : public TCPPFruityPlug {
public:
    int ParamValue[NumParamsConst];
    TOsc Osc[nOsc];
	CPtrList VoiceList;
    CDialog *editor;

    virtual void _stdcall DestroyObject();
    virtual int _stdcall Dispatcher(int ID, int Index, int Value);
    virtual void _stdcall SaveRestoreState(IStream *Stream, BOOL Save);
    virtual void _stdcall GetName(int Section, int Index, int Value, char *Name);

    virtual int _stdcall ProcessParam(int Index, int Value, int RECFlags);

    virtual void _stdcall Gen_Render(PWAV32FS DestBuffer, int &Length);

    virtual TVoiceHandle _stdcall TriggerVoice(PVoiceParams VoiceParams, int SetTag);
    virtual void _stdcall Voice_Release(TVoiceHandle Handle);
    virtual void _stdcall Voice_Kill(TVoiceHandle Handle);

    // FPF_EventController
    virtual void _stdcall NewTick();

    // FPF_MIDITick
    virtual void _stdcall MIDITick();

    // internal
    void KillAllVoices();
    TTestPlug(int SetTag, TFruityPlugHost *Host);
    int Voice_Render_Internal(TVoiceHandle Handle, PWaveT DestBuffer, int &Length);
};


#endif
