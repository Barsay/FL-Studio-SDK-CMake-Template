#pragma once

#include <list>
#include <Windows.h>
#include "fp_cplug.h"


enum
{
	paramVolume	= 0,	// 0..100
	NumParamsConst
};



class TVoice
{
public:
	intptr_t HostTag;
	TVoiceParams *Params;
	bool IsReleased;
    unsigned int Position;
    float CurrentPitch;
    int Speed;
    float LastLVol;
    float LastRVol;

	TVoice():	HostTag(0), Params(NULL), IsReleased(false), Position(0), CurrentPitch(0), Speed(0), LastLVol(0), LastRVol(0)	{}
};

class TTestPlug :	public TCPPFruityPlug
{
private:
	std::list<TVoice*> VoiceList;	// we use a dynamic list for voices. A fixed array would limit the polyphony
	void ClearVoices();
public:
	int ParamValue[NumParamsConst];

	TTestPlug(int SetHostTag, TFruityPlugHost *SetPlugHost, HINSTANCE SetInstance);
	~TTestPlug();

	// note: (GM) means GUI & Mixer thread, (G) is only called from the GUI thread, (M) is only called from the Mixer thread
    virtual intptr_t _stdcall Dispatcher(intptr_t ID, intptr_t Index, intptr_t Value);  // (GM)
    virtual void _stdcall SaveRestoreState(IStream *Stream, BOOL Save);  // (G)
    virtual void _stdcall GetName(int Section, int Index, int Value, char *Name);  // (GM)   // names (see FPN_Param) (Name buffer is at least 256 chars long)
    virtual int _stdcall ProcessParam(int ThisIndex, int ThisValue, int RECFlags);  // (GM)

	// generator processing (can render less than length)
    virtual void _stdcall Gen_Render(PWAV32FS DestBuffer, int &Length);  // (M)			// if you're making an effect, implement Eff_Render instead

	// voice handling (not necessary for an effect)
    virtual TVoiceHandle _stdcall TriggerVoice(PVoiceParams VoiceParams, intptr_t SetTag);  // (GM)
    virtual void _stdcall Voice_Release(TVoiceHandle Handle);  // (GM)
    virtual void _stdcall Voice_Kill(TVoiceHandle Handle);  // (GM)
    virtual int _stdcall Voice_ProcessEvent(TVoiceHandle Handle, int EventID, int EventValue, int Flags);  // (GM)
};
