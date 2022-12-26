// SynthForm.cpp : implementation file
//

#include "StdAfx.h"
#include "FruityPlug.h"
#include "SynthForm.h"
#include "../../../../Desktop/FLSDK/source/c/fp_plugclass.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SynthEditorForm dialog


SynthEditorForm::SynthEditorForm(CWnd* pParent /*=NULL*/)
	: CDialog(SynthEditorForm::IDD, pParent)
{
	//{{AFX_DATA_INIT(SynthEditorForm)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	// create our popup menu
	ContextMenu = CreatePopupMenu();
	PopupParameter = -1;
}


SynthEditorForm::~SynthEditorForm()
{
	// destroy our popup menu and all subitems
	int count = GetMenuItemCount(ContextMenu);
	while (count) {
		DeleteMenu(ContextMenu, count-1, MF_BYPOSITION);
		count--;
	}
	DestroyMenu(ContextMenu);
}


void SynthEditorForm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SynthEditorForm)
	DDX_Control(pDX, IDC_ControlSlider, m_ControlSlider);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SynthEditorForm, CDialog)
	//{{AFX_MSG_MAP(SynthEditorForm)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_ControlSlider, OnReleasedcaptureControlSlider)
	ON_WM_CREATE()
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SynthEditorForm message handlers

void SynthEditorForm::OnReleasedcaptureControlSlider(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here

	*pResult = 0;

	FruityPlug->ProcessParam(0, m_ControlSlider.GetPos(), REC_UpdateValue | REC_ShowHint);
	FruityPlug->PlugHost->OnParamChanged(FruityPlug->HostTag, 0, m_ControlSlider.GetPos());
}

void SynthEditorForm::OnContextMenu(CWnd* pWnd, CPoint point)
{
	// TODO: Add your message handler code here

	CWnd *p = pWnd;
	int param = -1;

	for (int i = 0; i < NumParamsConst; i++)
		if (p->m_hWnd == (void *)ParamCtrl[i]->m_hWnd)
		{
			param = i;
			break;
		}

	if (param < 0)
		return;

	FruityPlug->AdjustParamPopup(ContextMenu, param, 0, DefaultMenuID);

	PopupParameter = param;
	BOOL r = TrackPopupMenu(ContextMenu, TPM_RETURNCMD | TPM_RIGHTBUTTON, point.x, point.y, 0, pWnd->m_hWnd, NULL);

	if (r) {
	    FruityPlug->PlugHost->Dispatcher(FruityPlug->HostTag, FHD_ParamMenu, PopupParameter, r-DefaultMenuID);
	}
}
