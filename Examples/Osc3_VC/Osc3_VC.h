// Osc3_VC.h : main header file for the OSC3_VC DLL
//

#if !defined(AFX_OSC3_VC_H__7205B29F_2A3D_4892_B5CC_9C890817FE60__INCLUDED_)
#define AFX_OSC3_VC_H__7205B29F_2A3D_4892_B5CC_9C890817FE60__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// COsc3_VCApp
// See Osc3_VC.cpp for the implementation of this class
//

class COsc3_VCApp : public CWinApp
{
public:
	COsc3_VCApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COsc3_VCApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(COsc3_VCApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OSC3_VC_H__7205B29F_2A3D_4892_B5CC_9C890817FE60__INCLUDED_)
