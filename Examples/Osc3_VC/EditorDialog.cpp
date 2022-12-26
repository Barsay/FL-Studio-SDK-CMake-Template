// EditorDialog.cpp : implementation file
//

#include "StdAfx.h"
#include "Osc3_VC.h"
#include "EditorDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditorDialog dialog


CEditorDialog::CEditorDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CEditorDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEditorDialog)
	//}}AFX_DATA_INIT

    ParamCtrl[pOsc1Shape] = &m_Osc1Shape;
    ParamCtrl[pOsc1Coarse] = &m_Osc1Coarse;
    ParamCtrl[pOsc1Fine] = &m_Osc1Fine;
    ParamCtrl[pOsc2Level] = &m_Osc2Level;
	ParamCtrl[pOsc2Shape] = &m_Osc2Shape;
	ParamCtrl[pOsc2Coarse] = &m_Osc2Coarse;
	ParamCtrl[pOsc2Fine] = &m_Osc2Fine;
    ParamCtrl[pOsc3Level] = &m_Osc3Level;
	ParamCtrl[pOsc3Shape] = &m_Osc3Shape;
	ParamCtrl[pOsc3Coarse] = &m_Osc3Coarse;
	ParamCtrl[pOsc3Fine] = &m_Osc3Fine;

	// create our popup menu
	ContextMenu = CreatePopupMenu();
	PopupParameter = -1;
}

CEditorDialog::~CEditorDialog()
{
	// destroy our popup menu and all subitems
	int count = GetMenuItemCount(ContextMenu);
	while (count) {
		DeleteMenu(ContextMenu, count-1, MF_BYPOSITION);
		count--;
	}
	DestroyMenu(ContextMenu);
}

void CEditorDialog::InitControls()
{
	m_Osc1Shape.SetRange(0, 4);
	m_Osc1Coarse.SetRange(-24, 24);
	m_Osc1Fine.SetRange(-100, 100);
	m_Osc2Level.SetRange(0, 128);
	m_Osc2Shape.SetRange(0, 4);
	m_Osc2Coarse.SetRange(-24, 24);
	m_Osc2Fine.SetRange(-100, 100);
	m_Osc3Level.SetRange(0, 128);
	m_Osc3Shape.SetRange(0, 4);
	m_Osc3Coarse.SetRange(-24, 24);
	m_Osc3Fine.SetRange(-100, 100);

	m_Osc1Shape.SetPos(0);
	m_Osc1Coarse.SetPos(0);
	m_Osc1Fine.SetPos(0);
	m_Osc2Level.SetPos(64);
	m_Osc2Shape.SetPos(0);
	m_Osc2Coarse.SetPos(-12);
	m_Osc2Fine.SetPos(0);
	m_Osc3Level.SetPos(32);
	m_Osc3Shape.SetPos(0);
	m_Osc3Coarse.SetPos(-24);
	m_Osc3Fine.SetPos(0);
}


void CEditorDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditorDialog)
	DDX_Control(pDX, IDC_Osc1Shape, m_Osc1Shape);
	DDX_Control(pDX, IDC_Osc1Fine, m_Osc1Fine);
	DDX_Control(pDX, IDC_Osc1Coarse, m_Osc1Coarse);
	DDX_Control(pDX, IDC_SLIDER6, m_Osc3Coarse);
	DDX_Control(pDX, IDC_SLIDER9, m_Osc2Coarse);
	DDX_Control(pDX, IDC_SLIDER8, m_Osc3Fine);
	DDX_Control(pDX, IDC_SLIDER4, m_Osc3Shape);
	DDX_Control(pDX, IDC_SLIDER2, m_Osc2Shape);
	DDX_Control(pDX, IDC_SLIDER12, m_Osc3Level);
	DDX_Control(pDX, IDC_SLIDER1, m_Osc2Level);
	DDX_Control(pDX, IDC_SLIDER10, m_Osc2Fine);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEditorDialog, CDialog)
	//{{AFX_MSG_MAP(CEditorDialog)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER1, OnReleasedcaptureOsc2Level)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER10, OnReleasedcaptureOsc2Fine)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER12, OnReleasedcaptureOsc3Level)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER2, OnReleasedcaptureOsc2Shape)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER4, OnReleasedcaptureOsc3Shape)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER6, OnReleasedcaptureOsc3Coarse)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER8, OnReleasedcaptureOsc3Fine)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER9, OnReleasedcaptureOsc2Coarse)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_Osc1Coarse, OnReleasedcaptureOsc1Coarse)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_Osc1Fine, OnReleasedcaptureOsc1Fine)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_Osc1Shape, OnReleasedcaptureOsc1Shape)
	ON_WM_RBUTTONUP()
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditorDialog message handlers


void CEditorDialog::OnReleasedcaptureOsc2Level(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here

	int param = pOsc2Level;
	int pos = m_Osc2Level.GetPos();

    FruityPlug->ProcessParam(param, pos, REC_UpdateValue | REC_ShowHint);
    FruityPlug->PlugHost->OnParamChanged(FruityPlug->HostTag, param, pos);

	*pResult = 0;
}

void CEditorDialog::OnReleasedcaptureOsc2Fine(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here

	int param = pOsc2Fine;
	int pos = m_Osc2Fine.GetPos();

    FruityPlug->ProcessParam(param, pos, REC_UpdateValue | REC_ShowHint);
    FruityPlug->PlugHost->OnParamChanged(FruityPlug->HostTag, param, pos);

	*pResult = 0;
}

void CEditorDialog::OnReleasedcaptureOsc3Level(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here

	int param = pOsc3Level;
	int pos = m_Osc3Level.GetPos();

    FruityPlug->ProcessParam(param, pos, REC_UpdateValue | REC_ShowHint);
    FruityPlug->PlugHost->OnParamChanged(FruityPlug->HostTag, param, pos);

	*pResult = 0;
}

void CEditorDialog::OnReleasedcaptureOsc2Shape(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here

	int param = pOsc2Shape;
	int pos = m_Osc2Shape.GetPos();

    FruityPlug->ProcessParam(param, pos, REC_UpdateValue | REC_ShowHint);
    FruityPlug->PlugHost->OnParamChanged(FruityPlug->HostTag, param, pos);

	*pResult = 0;
}

void CEditorDialog::OnReleasedcaptureOsc3Shape(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here

	int param = pOsc3Shape;
	int pos = m_Osc3Shape.GetPos();

    FruityPlug->ProcessParam(param, pos, REC_UpdateValue | REC_ShowHint);
    FruityPlug->PlugHost->OnParamChanged(FruityPlug->HostTag, param, pos);

	*pResult = 0;
}

void CEditorDialog::OnReleasedcaptureOsc3Coarse(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here

	int param = pOsc3Coarse;
	int pos = m_Osc3Coarse.GetPos();

    FruityPlug->ProcessParam(param, pos, REC_UpdateValue | REC_ShowHint);
    FruityPlug->PlugHost->OnParamChanged(FruityPlug->HostTag, param, pos);

	*pResult = 0;
}

void CEditorDialog::OnReleasedcaptureOsc3Fine(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here

	int param = pOsc3Fine;
	int pos = m_Osc3Fine.GetPos();

    FruityPlug->ProcessParam(param, pos, REC_UpdateValue | REC_ShowHint);
    FruityPlug->PlugHost->OnParamChanged(FruityPlug->HostTag, param, pos);

	*pResult = 0;
}

void CEditorDialog::OnReleasedcaptureOsc2Coarse(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here

	int param = pOsc2Coarse;
	int pos = m_Osc2Coarse.GetPos();

    FruityPlug->ProcessParam(param, pos, REC_UpdateValue | REC_ShowHint);
    FruityPlug->PlugHost->OnParamChanged(FruityPlug->HostTag, param, pos);

	*pResult = 0;
}

void CEditorDialog::OnReleasedcaptureOsc1Coarse(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here
	int param = pOsc1Coarse;
	int pos = m_Osc1Coarse.GetPos();

	FruityPlug->ProcessParam(param, pos, REC_UpdateValue | REC_ShowHint);
	FruityPlug->PlugHost->OnParamChanged(FruityPlug->HostTag, param, pos);

	*pResult = 0;
}

void CEditorDialog::OnReleasedcaptureOsc1Fine(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here
    int param = pOsc1Fine;
	int pos = m_Osc1Fine.GetPos();

	FruityPlug->ProcessParam(param, pos, REC_UpdateValue | REC_ShowHint);
	FruityPlug->PlugHost->OnParamChanged(FruityPlug->HostTag, param, pos);


	*pResult = 0;
}

void CEditorDialog::OnReleasedcaptureOsc1Shape(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here
	int param = pOsc1Shape;
	int pos = m_Osc1Shape.GetPos();

	FruityPlug->ProcessParam(param, pos, REC_UpdateValue | REC_ShowHint);
	FruityPlug->PlugHost->OnParamChanged(FruityPlug->HostTag, param, pos);

	*pResult = 0;
}

void CEditorDialog::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CDialog::OnRButtonUp(nFlags, point);
}

void CEditorDialog::OnContextMenu(CWnd* pWnd, CPoint point)
{
	// TODO: Add your message handler code here

	CWnd *p = pWnd;  //->GetActiveWindow();
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

BOOL CEditorDialog::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your specialized code here and/or call the base class


	return CDialog::OnCommand(wParam, lParam);
}

BOOL CEditorDialog::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}
