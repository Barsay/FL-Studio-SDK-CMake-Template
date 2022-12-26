//---------------------------------------------------------------------------
#include "StdAfx.h"
#include <ObjIdl.h>

#include "TestPlug.h"
#include "SynthForm.h"

// the information structure describing this plugin to the host
TFruityPlugInfo PlugInfo = {
    CurrentSDKVersion,
    "InternalController_VC",
    "IC VC",
    FPF_Type_Effect | FPF_Type_Visual,  // FPF_Type_Visual means we don't process any sound
    NumParamsConst,
    0,                                  // infinite polyphony (it's an effect plugin)
    1                                   // one internal controller
};


extern "C" __declspec(dllexport) TFruityPlug * _stdcall CreatePlugInstance(TFruityPlugHost *Host, int Tag)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

    TTestPlug* plug = new TTestPlug(Tag, Host);
    return (TFruityPlug *)plug;
};


// TTestPlug
TTestPlug::TTestPlug(int Tag, TFruityPlugHost *Host)
    : TCPPFruityPlug(Tag, Host, 0)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetInstanceHandle(AfxGetInstanceHandle());

    Info = &PlugInfo;

    // create the editor form
    EditorForm = new SynthEditorForm;
	EditorForm->Create(IDD_SYNTHEDITORFORM_DIALOG);

    SynthEditorForm *Form = ((SynthEditorForm *)EditorForm);
    Form->FruityPlug = this;

	// initialize the controls on the editor form
	Form->m_ControlSlider.SetRange(0, 65536);
	Form->m_ControlSlider.SetPos(32768);

    // get all the parameter controls into the ParamCtrl array
    Form->ParamCtrl[0] = &(Form->m_ControlSlider);

    // set the parameters to their default values
    // (read from the initial values of the controls)
    for (int i = 0; i < NumParamsConst; i++)
        ParamValue[i] = Form->ParamCtrl[i]->GetPos();
}

void _stdcall TTestPlug::DestroyObject()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	delete EditorForm;

    TCPPFruityPlug::DestroyObject();   // don't forget this
}

int _stdcall TTestPlug::Dispatcher(int ID, int Index, int Value)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

    switch (ID) {
        // show the editor
        case FPD_ShowEditor :
            if (Value == 0)
            {
                EditorForm->ShowWindow(SW_HIDE);
				SetParent(EditorForm->m_hWnd, 0);
            }
            else
            {
                SetParent(EditorForm->m_hWnd, (HWND)Value);
                EditorForm->ShowWindow(SW_SHOW);
            }
            EditorHandle = EditorForm->m_hWnd;
            break;
    }

    return 0;
}

void _stdcall TTestPlug::Idle()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

    TCPPFruityPlug::Idle();

    // do any idle processing you want here
    // but don't forget to call inherited
}

void _stdcall TTestPlug::SaveRestoreState(IStream *Stream, BOOL Save)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

    if (Save)
        Stream->Write(ParamValue, StateSizeConst, 0);
    else
    {
        Stream->Read(ParamValue, StateSizeConst, 0);
        ProcessAllParams();
    }
}

void _stdcall TTestPlug::GetName(int Section, int Index, int Value, char *Name)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

    switch (Section)
    {
        // for the parameter names, we look at the (long) hint of the parameter control
        case FPN_Param :
			switch (Index) {
				case 0 :  strcpy(Name, "Controller"); break;
			}
            break;

        // the name of our only internal controller
        case FPN_OutCtrl :
            switch (Index) {
				case 0 :  strcpy(Name, "Example Controller"); break;
			}
			break;
    }
}

int _stdcall TTestPlug::ProcessParam(int ThisIndex, int ThisValue, int RECFlags)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

    SynthEditorForm *Form = (SynthEditorForm *)EditorForm;
	CSliderCtrl *Control = Form->ParamCtrl[ThisIndex];

    // translate from 0..65536 to the parameter's range
    if (RECFlags & REC_FromMIDI)
        ThisValue = TranslateMidi(ThisValue, Control->GetRangeMin(), Control->GetRangeMax());

    // update the value in the ParamValue array
    if (RECFlags & REC_UpdateValue)
    {
        ParamValue[ThisIndex] = ThisValue;

        // if the parameter value has changed,
        // then we notify the host that the controller has changed
        // (!) beware of messages that are sent by (other ?) internal controllers
        // (!) convert the value from its own range to 0..65536
        if ((RECFlags & REC_InternalCtrl) == 0)
            PlugHost->OnControllerChanged(HostTag, ThisIndex, ThisValue);
    }
    // retrieve the value from the ParamValue array
    else if (RECFlags & REC_GetValue)
        ThisValue = ParamValue[ThisIndex];

    // update the parameter control's value
    if (RECFlags & REC_UpdateControl)
        Control->SetPos(ThisValue);

    // we show the parameter value as a hint
    if (RECFlags & REC_ShowHint)
        ShowHintMsg_Percent(ThisValue - Control->GetRangeMin(), Control->GetRangeMax() - Control->GetRangeMin() + 1);

    // make sure we return the value
    return ThisValue;
}

void _stdcall TTestPlug::Eff_Render(PWAV32FS SourceBuffer, PWAV32FS DestBuffer, int Length)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // we don't process any sound (see FPF_Type_Visual)
    // so Eff_Render will normally not get called
}

//---------------------------------------------------------------------------
#pragma package(smart_init)
