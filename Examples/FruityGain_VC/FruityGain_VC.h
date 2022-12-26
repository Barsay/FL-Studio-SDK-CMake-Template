// FruityGain_VC.h : main header file for the FRUITYGAIN_VC DLL
//

#if !defined(AFX_FRUITYGAIN_VC_H__FA48FFA6_B33D_40FF_9827_81F243511865__INCLUDED_)
#define AFX_FRUITYGAIN_VC_H__FA48FFA6_B33D_40FF_9827_81F243511865__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CFruityGain_VCApp
// See FruityGain_VC.cpp for the implementation of this class
//

class CFruityGain_VCApp : public CWinApp
{
public:
	CFruityGain_VCApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFruityGain_VCApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CFruityGain_VCApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FRUITYGAIN_VC_H__FA48FFA6_B33D_40FF_9827_81F243511865__INCLUDED_)
