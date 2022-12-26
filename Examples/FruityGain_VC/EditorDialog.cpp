// EditorDialog.cpp : implementation file
//

#include "StdAfx.h"
#include "FruityGain_VC.h"
#include "resource.h"

#include "EditorDialog.h"
#include "Gain.h"

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
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CEditorDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditorDialog)
	DDX_Control(pDX, IDC_SLIDER2, m_RightSlider);
	DDX_Control(pDX, IDC_SLIDER1, m_LeftSlider);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEditorDialog, CDialog)
	//{{AFX_MSG_MAP(CEditorDialog)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER1, OnReleasedcaptureLeftSlider)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER2, OnReleasedcaptureRightSlider)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditorDialog message handlers


void CEditorDialog::ControlsToParams(bool left)
{
    TFruityGain *plug = (TFruityGain *)Plugin;

    if (left)
    {
        plug->GainLeftInt = m_LeftSlider.GetPos();
        Plugin->PlugHost->OnParamChanged(plug->HostTag, prmGainLeft, plug->GainLeftInt);
    }
    else
    {
        plug->GainRightInt = m_RightSlider.GetPos();
        Plugin->PlugHost->OnParamChanged(plug->HostTag, prmGainRight, plug->GainRightInt);
    }
    plug->GainIntToSingle();
}

void CEditorDialog::ParamsToControls()
{
    TFruityGain *plug = (TFruityGain *)Plugin;

    m_LeftSlider.SetPos(plug->GainLeftInt);
    m_RightSlider.SetPos(plug->GainRightInt);
}

void CEditorDialog::OnReleasedcaptureLeftSlider(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here
	ControlsToParams(true);

	*pResult = 0;
}

void CEditorDialog::OnReleasedcaptureRightSlider(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here
	ControlsToParams(false);

	*pResult = 0;
}
