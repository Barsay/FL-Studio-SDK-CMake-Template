//---------------------------------------------------------------------------
#include <afxwin.h>
#include <ObjIdl.h>

#include "Gain.h"


// the information structure describing this plugin to the host
TFruityPlugInfo PlugInfo = {
    CurrentSDKVersion,
    "FruityGain_VC",
    "F.Gain VC",
    FPF_Type_Effect,
    NumParams,
    0  // infinite
};



extern "C" TFruityPlug * _stdcall CreatePlugInstance(TFruityPlugHost *Host, int Tag)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	TFruityGain *gain = new TFruityGain(Tag, Host);

	return (TFruityPlug *)gain;
};




// TFruityGain

TFruityGain::TFruityGain(int Tag, TFruityPlugHost *Host)
    : TCPPFruityPlug(Tag, Host, 0)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetInstanceHandle(AfxGetInstanceHandle());

    Info = &PlugInfo;

	editor = new CEditorDialog;
	editor->Create(IDD_DIALOG1);
	editor->Plugin = this;
	editor->m_LeftSlider.SetRange(0, 20);
	editor->m_RightSlider.SetRange(0, 20);

	ResetParams();
}

void _stdcall TFruityGain::DestroyObject()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

	delete editor;
}

int _stdcall TFruityGain::Dispatcher(int ID, int Index, int Value)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

    switch (ID) {
        // show the editor
        case FPD_ShowEditor :
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
    }

    return 0;
}

void _stdcall TFruityGain::Eff_Render(PWAV32FS SourceBuffer, PWAV32FS DestBuffer, int Length)
{
   float left, right;

   left = GainLeft;
   right = GainRight;

   for (int i = 0; i < Length; i++)
   {
        (DestBuffer)[i][0] = (SourceBuffer)[i][0] * left;
        (DestBuffer)[i][1] = (SourceBuffer)[i][1] * right;
   }
}

void TFruityGain::GainIntToSingle()
{
    // for safety when we update the actual value, we lock the critical section
    Lock();
    GainLeft = (GainLeftInt / 4.) + 1;
    GainRight = (GainRightInt / 4.) + 1;
    Unlock();  // and unlock it again when we're through (very important !)
}

void _stdcall TFruityGain::GetName(int Section, int Index, int Value, char *Name)
{
    if (Section == FPN_Param)
    {
        switch (Index) {
            case prmGainLeft  :  strcpy(Name, "Left Gain");  break;
            case prmGainRight :  strcpy(Name, "Right Gain");  break;
        }
    }
    else if (Section == FPN_ParamValue)
    {
        switch (Index) {
            case prmGainLeft  :  sprintf(Name, "%.2fx", GainLeft);  break;
            case prmGainRight :  sprintf(Name, "%.2fx", GainRight);  break;
        }
    }
}

void _stdcall TFruityGain::Idle()
{
/*
    TControl *Control;
    POINT P;

    if (GetCaptureControl() != 0)
        return;

    GetCursorPos(&P);
    Control = FindDragTarget(P, true);
    if (Control != 0)
    {
        if (strcmp(AppHint, Control->Hint.c_str()) != 0)
        {
            strcpy(AppHint, Control->Hint.c_str());
            PlugHost->OnHint(HostTag, AppHint);
        }
    }
*/
}

int _stdcall TFruityGain::ProcessParam(int Index, int Value, int RECFlags)
{
    if (Index < NumParams)
    {
        if (RECFlags & REC_FromMIDI != 0)
            Value = TranslateMidi(Value, GainMinimum, GainMaximum);

        if (RECFlags & REC_UpdateValue != 0)
        {
            switch(Index) {
                case prmGainLeft  :  GainLeftInt = Value;  break;
                case prmGainRight :  GainRightInt = Value;  break;
            }
            GainIntToSingle();
        }

        else if (RECFlags & REC_GetValue != 0)
        {
            switch (Index) {
                case prmGainLeft  :  Value = GainLeftInt;  break;
                case prmGainRight :  Value = GainRightInt;  break;
            }
        }

        if (RECFlags & REC_UpdateControl != 0)
            editor->ParamsToControls();
    }

    return Value;
}

void TFruityGain::ResetParams()
{
    // start with a gain of 1.5 of both channels
    GainLeftInt = 2;
    GainRightInt = 2;
    GainIntToSingle();  // translate the int gain to floating point value

    editor->ParamsToControls();
}

void _stdcall TFruityGain::SaveRestoreState(IStream *Stream, BOOL Save)
{
    unsigned long written, read;

    if (Save)
    {
        Stream->Write(&GainLeftInt, sizeof(long), &written);
        Stream->Write(&GainRightInt, sizeof(long), &written);
    }
    else
    {
        Stream->Read(&GainLeftInt, sizeof(long), &read);
        Stream->Read(&GainRightInt, sizeof(long), &read);

        GainIntToSingle();
        ProcessAllParams();
    }
}
