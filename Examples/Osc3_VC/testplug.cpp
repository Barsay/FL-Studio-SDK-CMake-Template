#include "EditorDialog.h"
#include "testplug.h"
#include "fp_plugclass.h"

const int nMaxGrains = 24;
const int GrainLength = 512;  // samples per grain

// voice
struct TPlugVoice {
    int HostTag;
    PVoiceParams Params;
    int Pos[nOsc];
    int State;
};
typedef TPlugVoice *PPlugVoice;

PWaveT SineWaveP;

TFruityPlugInfo PlugInfo = {
    CurrentSDKVersion,
    "osc3_VC",
    "Osc3",
    FPF_Type_FullGen,
    NumParamsConst,
    0  // infinite
    };

// create an initialized plugin & return a pointer to the struct
extern "C" TFruityPlug * _stdcall CreatePlugInstance(TFruityPlugHost *Host, int Tag)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    return new TTestPlug(Tag, Host);
}

// create the object
TTestPlug::TTestPlug(int SetTag, TFruityPlugHost *Host)
    : TCPPFruityPlug(SetTag, Host, 0)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetInstanceHandle(AfxGetInstanceHandle());

    Info = &PlugInfo;

    // init
    SineWaveP = PlugHost->WaveTables[0];

    editor = new CEditorDialog;
	editor->Create(IDD_DIALOG1);
	CEditorDialog *eddlg = (CEditorDialog *)editor;
	eddlg->InitControls();
	eddlg->FruityPlug = this;

	int n;
    for (n = 0; n < NumParamsConst; n++)
    {
        if (eddlg->ParamCtrl[n] != 0)
            ParamValue[n] = ((CSliderCtrl *)eddlg->ParamCtrl[n])->GetPos();
    }

    for (n = 0; n < Info->NumParams; n++)
        ProcessParam(n, ProcessParam(n, 0, REC_GetValue), REC_UpdateValue);
}


// destroy the object
void _stdcall TTestPlug::DestroyObject()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

    KillAllVoices();
	delete editor;
}


int _stdcall TTestPlug::Dispatcher(int ID, int Index, int Value)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

    switch (ID)
    {
        // show the editor
        case FPD_ShowEditor:
            if (Value == 0)
            {
                editor->ShowWindow(SW_HIDE);
                SetParent(editor->m_hWnd, 0);
            }
            else
            {
                SetParent(editor->m_hWnd, (HWND)Value);
                editor->ShowWindow(SW_SHOW);
            }
            EditorHandle = editor->m_hWnd;
            break;

        case FPD_SetSampleRate:
			AudioRenderer.setSmpRate(Value);
			PitchMul= MiddleCMul/AudioRenderer.getSmpRate();
            break;
    }

    return 0;
}


// save/restore the state to/from a stream
void _stdcall TTestPlug::SaveRestoreState(IStream *Stream, BOOL Save)
{
    if (Save)
        Stream->Write(&ParamValue, NumParamsConst*4, 0);
    else
    {
        Stream->Read(&ParamValue, NumParamsConst*4, 0);
        ProcessAllParams();
    }
}

// params
int _stdcall TTestPlug::ProcessParam(int ThisIndex, int ThisValue, int RECFlags)
{
    int o, i;
    float v;

    CEditorDialog *eddlg = (CEditorDialog *)editor;
    CSliderCtrl *slider = (CSliderCtrl *)eddlg->ParamCtrl[ThisIndex];

    if (ThisIndex < NumParamsConst)
    {
        if ((RECFlags & REC_FromMIDI) != 0)
            ThisValue = TranslateMidi(ThisValue, slider->GetRangeMin(), slider->GetRangeMax());
        if ((RECFlags & REC_UpdateValue) != 0)
            ParamValue[ThisIndex] = ThisValue;
        else if ((RECFlags & REC_GetValue) != 0)
            ThisValue = ParamValue[ThisIndex];

        ThisIndex++;
        o = ThisIndex >> 2;
        i = (ThisIndex & 3)-1;
        switch (i) {
            // shape
            case pOsc1Shape:
                Osc[o].ShapeP = PlugHost->WaveTables[ThisValue];
                break;

            // level
            case pOsc1Level:
                Osc[2].Level = ParamValue[pOsc3Level]*Div128;
                v = 1-Osc[2].Level;
                Osc[1].Level = v*ParamValue[pOsc2Level]*Div128;
                Osc[0].Level = v-Osc[1].Level;
                if ((RECFlags & REC_ShowHint) != 0)
                    ShowHintMsg_Percent(ThisValue, 128);
                break;

            // pitch
            case pOsc1Coarse:
                break;
            case pOsc1Fine:
                Osc[o].Pitch = ParamValue[pOsc1Coarse+o*4]*100+ParamValue[pOsc1Fine+o*4];
                if ((RECFlags & REC_ShowHint) != 0)
                    ShowHintMsg_Pitch(ThisValue, i-pOsc1Coarse);
                break;

        }

        if ((RECFlags & REC_UpdateControl) != 0)
            slider->SetPos(ThisValue);
    }

    return ThisValue;
}


void _stdcall TTestPlug::GetName(int Section, int Index, int Value, char *Name)
{
    if (Section == FPN_Param){
		switch (Index) {
			case pOsc1Shape    :  strcpy(Name, "Osc1 Shape"); break;
			case pOsc1Coarse   :  strcpy(Name, "Osc1 Coarse"); break;
			case pOsc1Fine     :  strcpy(Name, "Osc1 Fine"); break;
			case pOsc2Level    :  strcpy(Name, "Osc2 Level"); break;
			case pOsc2Shape	   :  strcpy(Name, "Osc2 Shape"); break;
			case pOsc2Coarse   :  strcpy(Name, "Osc2 Coarse"); break;
			case pOsc2Fine     :  strcpy(Name, "Osc2 Fine"); break;
			case pOsc3Level    :  strcpy(Name, "Osc3 Level"); break;
			case pOsc3Shape    :  strcpy(Name, "Osc3 Shape"); break;
			case pOsc3Coarse   :  strcpy(Name, "Osc3 Coarse"); break;
			case pOsc3Fine     :  strcpy(Name, "Osc3 Fine"); break;
		}
    }
}

// create a new voice
TVoiceHandle _stdcall TTestPlug::TriggerVoice(PVoiceParams VoiceParams, int SetTag)
{
    PPlugVoice Voice;

    // create & init
    Voice = new TPlugVoice;
    Voice->HostTag = SetTag;

    for (int n = 0; n < nOsc; n++)
        Voice->Pos[n] = 0;
    Voice->Params = VoiceParams;
    Voice->State = 1;   // start the attack envelope

    // add to the list
    VoiceList.AddTail(Voice);

    return (TVoiceHandle)Voice;
}


void _stdcall TTestPlug::Voice_Release(TVoiceHandle Handle)
{
    //Voice_Kill(Handle);
    //(PPlugVoice)Handle.State = -1;  // releasing
}


// free a voice
void _stdcall TTestPlug::Voice_Kill(TVoiceHandle Handle)
{
	POSITION pos = VoiceList.Find((void *) Handle);
    VoiceList.RemoveAt(pos);
    delete (PPlugVoice)Handle;

}


void TTestPlug::KillAllVoices()
{
    while (VoiceList.GetCount() > 0)
    {
        PPlugVoice voice = (PPlugVoice)VoiceList.GetAt(0);
        PlugHost->Voice_Kill(voice->HostTag, true);
    }
}





// add an osc
int AddOsc(PWaveT SourceBuffer, PWaveT DestBuffer, int Length, int Pos, int Speed, float Level)
{
    float i;
    unsigned long position = Pos;

    for (int n = 0; n < Length; n++)
    {
        // get input
        i = (*SourceBuffer)[position >> WaveT_Shift] * Level;

        // store output
        (*DestBuffer)[n] = (*DestBuffer)[n] + i;

        position += Speed;
    }

    return position;
}

// add an osc (replace)
int PutOsc(PWaveT SourceBuffer, PWaveT DestBuffer, int Length, int Pos, int Speed, float Level)
{
    float i;
    unsigned long position = Pos;

    for (int n = 0; n < Length; n++)
    {
        // get input
        i = (*SourceBuffer)[position >> WaveT_Shift] * Level;

        // store output
        (*DestBuffer)[n] = i;

        position += Speed;
    }

    return position;
}

void CopyMonoToStereo(PWaveT SourceBuffer, PWAV32FS DestBuffer, int Length, int Pan)
{
    float LeftPan = 1.;
    float RightPan = 1.;
    if (Pan < 0)
        RightPan = (Pan+64) / 64.f;
    else if (Pan > 0)
        LeftPan = (64-Pan) / 64.f;


    for (int i = 0; i < Length; i++)
    {
        (DestBuffer)[i][0] = (DestBuffer)[i][0] + (SourceBuffer)[i][0] * LeftPan;
        (DestBuffer)[i][1] = (DestBuffer)[i][1] + (SourceBuffer)[i][1] * RightPan;
    }
}


void ApplyEnvelope(PWaveT Buffer, int Length, int &State)
{
    if (State == 0)   // nothing to do if we have to sustain
        return;

    float envelope;

    for (int i = 0; i < Length; i++)
    {
        if (State == 1)                // apply an attacking envelope
            envelope = (1.*i) / Length;
        else if (State == -1)          // apply a releasing envelope
            envelope = 1.*(Length-i) / Length;

        (*Buffer)[i] = (*Buffer)[i] * envelope;
    }

    if (State == 1)
        State = 0;    // proceed to sustain
    else if (State == -1)
        State = -2;   // next pass we kill the voice
}


int TTestPlug::Voice_Render_Internal(TVoiceHandle Handle, PWaveT DestBuffer, int &Length)
{
    int p;
    int Speed;
    BOOL Replace;

    PPlugVoice voice = (PPlugVoice)Handle;

    // compute osc speed & add them
    p = voice->Params->FinalLevels.Pitch;
    Replace = true;
    for (int o = 0; o < nOsc; o++)
    {
        Speed = GetStep_Cents(p + Osc[o].Pitch);
        T32Bit temp;
        temp.s = Osc[o].Level;
        if (temp.i == 0)
            voice->Pos[o] += Speed*Length;
        else if (Replace)
        {
            voice->Pos[o] = PutOsc(Osc[o].ShapeP, DestBuffer, Length, voice->Pos[o], Speed,
				                   Osc[o].Level * voice->Params->FinalLevels.Vol);
            Replace = false;
        }
        else
            voice->Pos[o] = AddOsc(Osc[o].ShapeP, DestBuffer, Length, voice->Pos[o], Speed,
			                       Osc[o].Level * voice->Params->FinalLevels.Vol);
    }

    return FVR_Ok;
}


void _stdcall TTestPlug::Gen_Render(PWAV32FS DestBuffer, int &Length)
{
    if (VoiceList.GetCount() == 0)
        Length = 0;       // nothing to render, so tell it
    else
    {
        for (int n = VoiceList.GetCount()-1; n >= 0; n--)
        {
            PWaveT temp = (PWaveT)malloc(Length << 2);
			memset(temp, 0, Length << 2);

			POSITION pos = VoiceList.FindIndex(n);
            PPlugVoice voice = (PPlugVoice)(VoiceList.GetAt(pos));
            if (voice->State == -2)
                // let the host kill the voice
                PlugHost->Voice_Kill(voice->HostTag, true);
            else
			{
                // render it
                Voice_Render_Internal((int)voice, temp, Length);
				ApplyEnvelope(temp, Length, voice->State);
                CopyMonoToStereo(temp, DestBuffer, Length, voice->Params->FinalLevels.Pan);
			}

            free(temp);
        }
    }
}

void _stdcall TTestPlug::NewTick()
{
}

void _stdcall TTestPlug::MIDITick()
{
}

