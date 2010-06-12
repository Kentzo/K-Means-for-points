// KMeansDoc.cpp : implementation of the CKMeansDoc class
//

#include "stdafx.h"
#include "KMeans.h"

#include "KMeansDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CKMeansDoc

IMPLEMENT_DYNCREATE(CKMeansDoc, CDocument)

BEGIN_MESSAGE_MAP(CKMeansDoc, CDocument)
END_MESSAGE_MAP()


// CKMeansDoc construction/destruction

CKMeansDoc::CKMeansDoc()
{
	// TODO: add one-time construction code here

}

CKMeansDoc::~CKMeansDoc()
{
}

BOOL CKMeansDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CKMeansDoc serialization

void CKMeansDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CKMeansDoc diagnostics

#ifdef _DEBUG
void CKMeansDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CKMeansDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CKMeansDoc commands
