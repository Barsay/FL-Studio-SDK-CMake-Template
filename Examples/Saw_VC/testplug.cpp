#include "testplug.h"



const int PlugVersion = 1;	// used in SaveRestoreState



// the information structure describing this plugin to the host
TFruityPlugInfo PlugInfo = {
	CurrentSDKVersion,
	"Saw_VC",
	"Saw",
	FPF_Type_FullGen,
	NumParamsConst,
	0,                                  // infinite polyphony
	0                                   // no internal controllers
};



LRESULT CALLBACK PlgWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// get plugin pointer
	TTestPlug *plugin = (TTestPlug*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
	if (!plugin)
		return DefWindowProc(hwnd, message, wParam, lParam);

	// erase background message
	if (message == WM_ERASEBKGND)
	{
		return 0;
	}

	// paint message
	if (message == WM_PAINT)
	{
		// start window paint
		PAINTSTRUCT ps;
		HDC const hdc = BeginPaint(hwnd, &ps);

		// paint background
		// -- create brush and pen
		HBRUSH brush = CreateSolidBrush(RGB(100, 100, 100));
		HGDIOBJ oldbrush = SelectObject(hdc, brush);
		HPEN pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		HGDIOBJ oldpen = SelectObject(hdc, pen);
		// -- fill background
		RECT r;
		r.left = 0;
		r.top = 0;
		r.right = 300;
		r.bottom = 200;
		FillRect(hdc, &r, brush);
		// -- paint text
		TextOut(hdc, 10, 10, "SAW", 3);
		// -- delete brush and pen
		SelectObject(hdc, oldbrush);
		DeleteObject(brush);
		SelectObject(hdc, oldpen);
		DeleteObject(pen);

		// end paint operation
		EndPaint(hwnd,&ps);
		return 0;
	}

	// default
	return DefWindowProc(hwnd,message,wParam,lParam);
}



TTestPlug::TTestPlug(int SetHostTag, TFruityPlugHost *SetPlugHost, HINSTANCE SetInstance)
:	TCPPFruityPlug(SetHostTag, SetPlugHost, SetInstance),
	VoiceList()
{
	Info = &PlugInfo;

	ParamValue[paramVolume] = 80;

	// register our window class (not necessary if you use a UI sdk
	WNDCLASS windowClass;
	windowClass.style = CS_DBLCLKS;
	windowClass.lpfnWndProc = PlgWndProc;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = HInstance;
	windowClass.hIcon = 0;
	windowClass.hCursor = 0;
	windowClass.hbrBackground = 0;
	windowClass.lpszMenuName = 0;
	windowClass.lpszClassName = "SawVCExampleWindow";
	RegisterClass(&windowClass);
}

TTestPlug::~TTestPlug()
{
	ClearVoices();	// just in case
}

intptr_t _stdcall TTestPlug::Dispatcher(intptr_t ID, intptr_t Index, intptr_t Value)
{
	intptr_t r = TCPPFruityPlug::Dispatcher(ID, Index, Value);
	if (r != 0)
		return r;

	switch (ID)
	{
		// show or hide the plugin editor
		case FPD_ShowEditor:
			if (Value == 0)	// hide (no parent window)
			{
				DestroyWindow(EditorHandle);
				EditorHandle = 0;
			}
			else			// show
			{
				EditorHandle = CreateWindowEx(0, "SawVCExampleWindow", "SawVCExampleWindow", WS_CHILD | WS_VISIBLE, 0, 0, 300, 200, (HWND)Value, NULL, HInstance, NULL);
				SetWindowLongPtr(EditorHandle, GWLP_USERDATA, (LONG_PTR)this);
			}
			break;

		// set the samplerate
		case FPD_SetSampleRate:
			AudioRenderer.setSmpRate(Value);
			PitchMul = MiddleCMul/AudioRenderer.getSmpRate();
			break;
	}

	return r;
}

void _stdcall TTestPlug::SaveRestoreState(IStream *Stream, BOOL Save)
{
	if (Save)
	{
		// first write a version number, so we can change the format later on if we want to
		long version = PlugVersion;
		Stream->Write(&version, 4, NULL);

		// save your settings to Stream
		Stream->Write(&ParamValue, sizeof(ParamValue), NULL);
	}
	else
	{
		// read the saved version number
		long version = 0xFFFFFFFF;
		Stream->Read(&version, 4, NULL);
		if (version <= PlugVersion)	// we know what to do if the version is older than our own
		{
			// load previously saved settings
			Stream->Read(&ParamValue, sizeof(ParamValue), NULL);
		}
	}
}

void _stdcall TTestPlug::GetName(int Section, int Index, int Value, char *Name)
{
	if (Section == FPN_Param)
	{
		switch (Index)
		{
			case paramVolume:	strcpy_s(Name, 256, "Volume");
		}
	}
}

int _stdcall TTestPlug::ProcessParam(int ThisIndex, int ThisValue, int RECFlags)
{
	if ((RECFlags & REC_FromMIDI) == REC_FromMIDI)
		ThisValue = ThisValue*100/65536;	// REC_FromMIDI means the value is between 0 and 65536. Here we convert it to our own range (volume parameter will be between 0 and 100)

	if ((RECFlags & REC_GetValue) == REC_GetValue)
		ThisValue = ParamValue[ThisIndex];
	if ((RECFlags & REC_UpdateValue) == REC_UpdateValue)
		ParamValue[ThisIndex] = ThisValue;

	if ((RECFlags & REC_UpdateControl) == REC_UpdateControl)
	{
		// update the parameter's control on the GUI now
	}

	return ThisValue;	// return the value (in case of REC_FromMIDI or REC_GetValue)
}

void _stdcall TTestPlug::Gen_Render(PWAV32FS DestBuffer, int &Length)
{
	float volume = ParamValue[paramVolume]/100.f;	// get the volume from 0 to 1.0
	float LVol, RVol;

    PWAV32FM Buffer = (PWAV32FM)PlugHost->TempBuffers[0];     // get our temporary buffer from the host
	PWaveT SawTable = PlugHost->WaveTables[3];

	// render each voice here
	std::list<TVoice*>::iterator it;
	for (it = VoiceList.begin(); it != VoiceList.end(); ++it)
	{
		TVoice *v = *it;

		// ramp to zero if the voice was released
		if (v->IsReleased)
		{
			LVol = 0;
			RVol = 0;
		}
		// let the host compute volumes taking into account the per-voice pan and volume
		else
			PlugHost->ComputeLRVol(LVol, RVol, v->Params->FinalLevels.Pan, v->Params->FinalLevels.Vol);

		// change the pitch if necessary (slides)
		if (v->Params->FinalLevels.Pitch != v->CurrentPitch)
		{
			v->CurrentPitch = v->Params->FinalLevels.Pitch;
			v->Speed = GetStep_Cents(v->CurrentPitch);
		}

		// copy samples from the saw wavetable to the destination buffer
		for (int j = 0; j < Length; j++)
		{
			int pos = v->Position >> WaveT_Shift;
			(Buffer)[j] = (*SawTable)[pos] * volume;
			// !!! make sure to disable any overflow checking in the compiler, as this is based on an overflow trick
			v->Position += v->Speed;
		}

  		// add the temporary buffer to the output buffer with ramping
		PlugHost->AddWave_32FM_32FS_Ramp(Buffer, DestBuffer, Length, LVol, RVol, v->LastLVol, v->LastRVol);
	}

	// kill voices that were released
	for (it = VoiceList.begin(); it != VoiceList.end(); ++it)
	{
		TVoice *v = *it;
		if (v->IsReleased)
			PlugHost->Voice_Kill(v->HostTag, TRUE);
	}
}

TVoiceHandle _stdcall TTestPlug::TriggerVoice(PVoiceParams VoiceParams, intptr_t SetTag)
{
	// create our new voice and set its parameters
	TVoice *v = new TVoice();
	v->HostTag = SetTag;
	v->Params = VoiceParams;
	v->IsReleased = false;
	v->CurrentPitch = v->Params->FinalLevels.Pitch;
	v->Speed = GetStep_Cents(v->CurrentPitch);

	// add it to our list
	VoiceList.push_back(v);

	// return a handle so the host can tell us when something happens to it
	// we use the voice class' pointer for this, since it's supposed to be unique within the process
	return (TVoiceHandle)v;
}

void _stdcall TTestPlug::Voice_Release(TVoiceHandle Handle)
{
	// handle is the value we returned in TriggerVoice, so it's really a pointer to a TVoice object
	TVoice *v = (TVoice*)Handle;

	// set it to the released state (will be handled in Gen_Render)
	v->IsReleased = true;
}

void _stdcall TTestPlug::Voice_Kill(TVoiceHandle Handle)
{
	// handle is the value we returned in TriggerVoice, so it's really a pointer to a TVoice object
	TVoice *v = (TVoice*)Handle;

	// remove it from the list
	VoiceList.remove(v);
}

int _stdcall TTestPlug::Voice_ProcessEvent(TVoiceHandle Handle, int EventID, int EventValue, int Flags)
{
	return 0;
}

void TTestPlug::ClearVoices()
{
	std::list<TVoice*>::iterator it;
	for (it = VoiceList.begin(); it != VoiceList.end(); ++it)
	{
		TVoice *v = *it;
		delete v;
	}
	VoiceList.clear();
}
