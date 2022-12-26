//---------------------------------------------------------------------------
#ifndef GAIN_H
#define GAIN_H

#include "fp_plugclass.h"
#include "fp_cplug.h"
#include "EditorDialog.h"


// the number of parameters
const int NumParams = 2;

// the parameter indexes
const int prmGainLeft  = 0;
const int prmGainRight = 1;

// minimum and maximum values of the gain parameters
const int GainMinimum = 0;
const int GainMaximum = 20;





class TFruityGain : public TCPPFruityPlug {
private:
public:
    int GainLeftInt;
    int GainRightInt;
    float GainLeft;
    float GainRight;
	CEditorDialog *editor;

    TFruityGain(int Tag, TFruityPlugHost *Host);

	virtual void _stdcall DestroyObject();
    virtual int _stdcall Dispatcher(int ID, int Index, int Value);
    virtual void _stdcall Idle();
    virtual void _stdcall SaveRestoreState(IStream *Stream, BOOL Save);

    // names (see FPN_Param) (Name must be at least 256 chars long)
    virtual void _stdcall GetName(int Section, int Index, int Value, char *Name);

    // events
    virtual int _stdcall ProcessParam(int Index, int Value, int RECFlags);

    // effect processing (source & dest can be the same)
    virtual void _stdcall Eff_Render(PWAV32FS SourceBuffer, PWAV32FS DestBuffer, int Length);

    // specific to this plugin
    void GainIntToSingle();
    void ResetParams();
};


//---------------------------------------------------------------------------
#endif
