// KMeans.h : main header file for the KMeans application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CKMeansApp:
// See KMeans.cpp for the implementation of this class
//

class CKMeansApp : public CWinApp
{
public:
	CKMeansApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CKMeansApp theApp;