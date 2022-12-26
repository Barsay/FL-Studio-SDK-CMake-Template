#if !defined(AFX_EDITORDIALOG_H__2127516D_756C_4766_B99F_CF6D02E3A595__INCLUDED_)
#define AFX_EDITORDIALOG_H__2127516D_756C_4766_B99F_CF6D02E3A595__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditorDialog.h : header file
//

#include <afxwin.h>
#include "resource.h"
#include <afxcmn.h>

#include "fp_plugclass.h"
#include "fp_cplug.h"
#include "testplug.h"

/////////////////////////////////////////////////////////////////////////////
// CEditorDialog dialog

class CEditorDialog : public CDialog
{
// Construction
public:
    CSliderCtrl *ParamCtrl[NumParamsConst];
    TCPPFruityPlug *FruityPlug;

	void InitControls();

	CEditorDialog(CWnd* pParent = NULL);   // standard constructor
	~CEditorDialog();

// Dialog Data
	//{{AFX_DATA(CEditorDialog)
	enum { IDD = IDD_DIALOG1 };
	CSliderCtrl	m_Osc1Shape;
	CSliderCtrl	m_Osc1Fine;
	CSliderCtrl	m_Osc1Coarse;
	CSliderCtrl	m_Osc3Coarse;
	CSliderCtrl	m_Osc2Coarse;
	CSliderCtrl	m_Osc3Fine;
	CSliderCtrl	m_Osc3Shape;
	CSliderCtrl	m_Osc2Shape;
	CSliderCtrl	m_Osc3Level;
	CSliderCtrl	m_Osc2Level;
	CSliderCtrl	m_Osc2Fine;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditorDialog)
	public:
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	HMENU ContextMenu;
	int PopupParameter;

	// Generated message map functions
	//{{AFX_MSG(CEditorDialog)
	afx_msg void OnReleasedcaptureOsc2Level(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureOsc2Fine(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureOsc3Level(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureOsc2Shape(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureOsc3Shape(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureOsc3Coarse(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureOsc3Fine(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureOsc2Coarse(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureOsc1Coarse(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureOsc1Fine(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureOsc1Shape(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITORDIALOG_H__2127516D_756C_4766_B99F_CF6D02E3A595__INCLUDED_)
