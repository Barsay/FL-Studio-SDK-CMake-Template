#if !defined(AFX_EDITORDIALOG_H__AAD2823B_3213_435D_A841_1A9A65E70125__INCLUDED_)
#define AFX_EDITORDIALOG_H__AAD2823B_3213_435D_A841_1A9A65E70125__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditorDialog.h : header file
//

#include "resource.h"
#include <afxcmn.h>
#include "fp_plugclass.h"
#include "fp_cplug.h"

/////////////////////////////////////////////////////////////////////////////
// CEditorDialog dialog

class CEditorDialog : public CDialog
{
// Construction
public:
    TCPPFruityPlug *Plugin;
    void ControlsToParams(bool left);
    void ParamsToControls();

	CEditorDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEditorDialog)
	enum { IDD = IDD_DIALOG1 };
	CSliderCtrl	m_RightSlider;
	CSliderCtrl	m_LeftSlider;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditorDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEditorDialog)
	afx_msg void OnReleasedcaptureLeftSlider(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureRightSlider(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITORDIALOG_H__AAD2823B_3213_435D_A841_1A9A65E70125__INCLUDED_)
