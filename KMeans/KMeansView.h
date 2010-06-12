// KMeansView.h : interface of the CKMeansView class
//


#pragma once

#include "PointKMeanClusterizer.h"
#include "MemDC.h"
#include <map>

class CKMeansView : public CScrollView
{
protected: // create from serialization only
	CKMeansView();
	DECLARE_DYNCREATE(CKMeansView)

// Attributes
public:
	CKMeansDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CKMeansView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

	CPointKMeanClusterizer clusterizer;
	std::map<CPoint, COLORREF> colors;
	CSize size;
	unsigned int num_points;
	unsigned int num_clusters;

	void DrawLine(const CPoint& first, const CPoint& second, CMemDC* pDC);
	void DrawPoint(const CPoint& point, CMemDC* pDC);
	void DrawKMean(const CPoint& kmean, CMemDC* pDC);
public:
	virtual void OnInitialUpdate();
	afx_msg void OnGenerate();
	afx_msg void OnGenerateUpdate(CCmdUI* pCmdUI);
	afx_msg void OnRun();
	afx_msg void OnRunUpdate(CCmdUI* pCmdUI);
	afx_msg void OnStop();
	afx_msg void OnStopUpdate(CCmdUI* pCmdUI);
	afx_msg void OnStep();
	afx_msg void OnStepUpdate(CCmdUI* pCmdUI);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
};

#ifndef _DEBUG  // debug version in KMeansView.cpp
inline CKMeansDoc* CKMeansView::GetDocument() const
   { return reinterpret_cast<CKMeansDoc*>(m_pDocument); }
#endif

