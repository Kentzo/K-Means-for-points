// KMeansDoc.h : interface of the CKMeansDoc class
//


#pragma once


class CKMeansDoc : public CDocument
{
protected: // create from serialization only
	CKMeansDoc();
	DECLARE_DYNCREATE(CKMeansDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CKMeansDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


