// FruityPlug.h : main header file for the FRUITYPLUG DLL
//

#if !defined(AFX_FRUITYPLUG_H__D61E2F92_7E37_431E_A388_5D9478FAF39D__INCLUDED_)
#define AFX_FRUITYPLUG_H__D61E2F92_7E37_431E_A388_5D9478FAF39D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "Resource.h"        // main symbols

/////////////////////////////////////////////////////////////////////////////
// CFruityPlugApp
// See FruityPlug.cpp for the implementation of this class
//

class CFruityPlugApp : public CWinApp
{
public:
	CFruityPlugApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFruityPlugApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CFruityPlugApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FRUITYPLUG_H__D61E2F92_7E37_431E_A388_5D9478FAF39D__INCLUDED_)
