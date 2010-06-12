// KMeansView.cpp : implementation of the CKMeansView class
//

#include "stdafx.h"
#include "KMeans.h"

#include "KMeansDoc.h"
#include "KMeansView.h"
#include "GenerateDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static const size_t POINT_RAD = 4;
static const size_t KMEAN_RAD = 6;

// CKMeansView

IMPLEMENT_DYNCREATE(CKMeansView, CScrollView)

BEGIN_MESSAGE_MAP(CKMeansView, CScrollView)
	ON_COMMAND(ID_GENERATE, OnGenerate)
	ON_UPDATE_COMMAND_UI(ID_GENERATE, OnGenerateUpdate)
	ON_COMMAND(ID_RUN, OnRun)
	ON_UPDATE_COMMAND_UI(ID_RUN, OnRunUpdate)
	ON_COMMAND(ID_STOP, OnStop)
	ON_UPDATE_COMMAND_UI(ID_STOP, OnStopUpdate)
	ON_COMMAND(ID_STEP, OnStep)
	ON_UPDATE_COMMAND_UI(ID_STEP, OnStepUpdate)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_VSCROLL()
END_MESSAGE_MAP()

// CKMeansView construction/destruction

CKMeansView::CKMeansView() : size(1024, 768), num_points(150), num_clusters(10)
{

}

CKMeansView::~CKMeansView()
{
}

BOOL CKMeansView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	return CScrollView::PreCreateWindow(cs);
}

// CKMeansView drawing

void CKMeansView::OnDraw(CDC* ppDC)
{
	CKMeansDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CMemDC pDC(ppDC);

	pDC.Rectangle(0, 0, size.cx, size.cy);
	CPen pen(PS_DOT, 1, RGB(150, 150, 150));
	CPen *oldPen = pDC.SelectObject(&pen);
	CLUSTERS clusters = clusterizer.GetClusters();
	CLUSTERS::const_iterator it = clusters.begin(), end = clusters.end();
	while (it != end) {
		CBrush *brush = NULL;
		if (colors.find(it->first) != colors.end()) {
			brush = new CBrush(colors[it->first]);
		}
		else {
			colors[it->first] = RGB(rand() % 255, rand() % 255, rand() % 255);
			brush = new CBrush(colors[it->first]);
		}
		CBrush *oldBrush = pDC.SelectObject(brush);

		CLUSTER::second_type::const_iterator pit = it->second.begin(), pend = it->second.end();
		while (pit != pend) {
			DrawLine(it->first, *pit, &pDC);
			DrawPoint(*pit, &pDC);
			++pit;
		}
		DrawKMean(it->first, &pDC);
		++it;

		pDC.SelectObject(oldBrush);
		brush->DeleteObject();
		delete brush;
	}
	pDC.SelectObject(oldPen);
	pen.DeleteObject();
}


// CKMeansView diagnostics

#ifdef _DEBUG
void CKMeansView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CKMeansView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CKMeansDoc* CKMeansView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CKMeansDoc)));
	return (CKMeansDoc*)m_pDocument;
}
#endif //_DEBUG


// CKMeansView message handlers

void CKMeansView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	clusterizer.Generate(num_points, num_clusters, CRect(CPoint(0, 0), size), 15);

	SetScrollSizes(MM_TEXT, size);
}

void CKMeansView::DrawLine(const CPoint& first, const CPoint& second, CMemDC* pDC) {
	pDC->MoveTo(first.x, first.y);
	pDC->LineTo(second.x, second.y);
}

void CKMeansView::DrawPoint(const CPoint& point, CMemDC* pDC) {
	pDC->Ellipse(point.x - POINT_RAD, point.y - POINT_RAD, point.x + POINT_RAD, point.y + POINT_RAD);
}

void CKMeansView::DrawKMean(const CPoint& kmean, CMemDC* pDC) {
	pDC->Rectangle(kmean.x - KMEAN_RAD, kmean.y - KMEAN_RAD, kmean.x + KMEAN_RAD, kmean.y + KMEAN_RAD);
}

void CKMeansView::OnGenerate() {
	CGenerateDialog dlg;
	dlg.m_height = size.cx;
	dlg.m_width = size.cy;
	dlg.m_points = num_points;
	dlg.m_clusters = num_clusters;
	if (dlg.DoModal() == IDOK) {
		CRect rect = CRect(0, 0, dlg.m_height, dlg.m_width);
		size = rect.Size();
		num_points = dlg.m_points;
		num_clusters = dlg.m_clusters;
		clusterizer.Generate(dlg.m_points, dlg.m_clusters, rect, 15);
		Invalidate();
		SetScrollSizes(MM_TEXT, rect.Size());
		colors.clear();
	}
}

void CKMeansView::OnGenerateUpdate(CCmdUI* pCmdUI) {
	if (clusterizer.IsRun())
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);
}

void CKMeansView::OnRun() {
	CGenerateDialog dlg;
	dlg.m_height = size.cx;
	dlg.m_width = size.cy;
	dlg.m_points = num_points;
	dlg.m_clusters = num_clusters;
	if (dlg.DoModal() == IDOK) {
		CRect rect = CRect(0, 0, dlg.m_height, dlg.m_width);
		size = rect.Size();
		num_points = dlg.m_points;
		num_clusters = dlg.m_clusters;
		clusterizer.Run(dlg.m_points, dlg.m_clusters, rect);
		Invalidate();
		SetScrollSizes(MM_TEXT, rect.Size());
		colors.clear();
	}
}

void CKMeansView::OnRunUpdate(CCmdUI* pCmdUI) {
	if (clusterizer.IsRun())
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);
}

void CKMeansView::OnStop() {
	clusterizer.Stop();
}

void CKMeansView::OnStopUpdate(CCmdUI* pCmdUI) {
	if (clusterizer.IsRun())
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

void CKMeansView::OnStep() {
	clusterizer.Step();
	Invalidate();
}

void CKMeansView::OnStepUpdate(CCmdUI* pCmdUI) {
	if (clusterizer.IsRun())
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

BOOL CKMeansView::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

void CKMeansView::OnPaint()
{
	/*CPaintDC dc(this);
	CMemDC pDC(&dc);

	pDC.Rectangle(0, 0, size.cx, size.cy);
	CPen pen(PS_DOT, 1, RGB(150, 150, 150));
	CPen *oldPen = pDC.SelectObject(&pen);
	CLUSTERS clusters = clusterizer.GetClusters();
	CLUSTERS::const_iterator it = clusters.begin(), end = clusters.end();
	while (it != end) {
		CBrush *brush = NULL;
		if (colors.find(it->first) != colors.end()) {
			brush = new CBrush(colors[it->first]);
		}
		else {
			colors[it->first] = RGB(rand() % 255, rand() % 255, rand() % 255);
			brush = new CBrush(colors[it->first]);
		}
		CBrush *oldBrush = pDC.SelectObject(brush);

		CLUSTER::second_type::const_iterator pit = it->second.begin(), pend = it->second.end();
		while (pit != pend) {
			DrawLine(it->first, *pit, &pDC);
			DrawPoint(*pit, &pDC);
			++pit;
		}
		DrawKMean(it->first, &pDC);
		++it;

		pDC.SelectObject(oldBrush);
		brush->DeleteObject();
		delete brush;
	}
	pDC.SelectObject(oldPen);
	pen.DeleteObject();*/

	CScrollView::OnPaint();
}

BOOL CKMeansView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	dwStyle |= WS_HSCROLL | WS_VSCROLL;

	return CScrollView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}
