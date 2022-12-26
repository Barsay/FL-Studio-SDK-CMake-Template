#if !defined(AFX_SYNTHFORM_H__6B921FAC_F1DD_4717_A24A_99FF454221A1__INCLUDED_)
#define AFX_SYNTHFORM_H__6B921FAC_F1DD_4717_A24A_99FF454221A1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SynthForm.h : header file
//

#include "StdAfx.h"
#include "TestPlug.h"

#include "Resource.h"


/////////////////////////////////////////////////////////////////////////////
// SynthEditorForm dialog

class SynthEditorForm : public CDialog
{
// Construction
public:
	TTestPlug *FruityPlug;
	CSliderCtrl *ParamCtrl[NumParamsConst];

	SynthEditorForm(CWnd* pParent = NULL);   // standard constructor
	~SynthEditorForm();

// Dialog Data
	//{{AFX_DATA(SynthEditorForm)
	enum { IDD = IDD_SYNTHEDITORFORM_DIALOG };
	CSliderCtrl	m_ControlSlider;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SynthEditorForm)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HMENU ContextMenu;
	int PopupParameter;

	// Generated message map functions
	//{{AFX_MSG(SynthEditorForm)
	afx_msg void OnReleasedcaptureControlSlider(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYNTHFORM_H__6B921FAC_F1DD_4717_A24A_99FF454221A1__INCLUDED_)
