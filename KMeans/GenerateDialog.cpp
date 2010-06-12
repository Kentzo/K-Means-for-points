// GenerateDialog.cpp : implementation file
//

#include "stdafx.h"
#include "KMeans.h"
#include "GenerateDialog.h"


// CGenerateDialog dialog

IMPLEMENT_DYNAMIC(CGenerateDialog, CDialog)

CGenerateDialog::CGenerateDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CGenerateDialog::IDD, pParent)
	, m_clusters(10)
	, m_height(800)
	, m_points(150)
	, m_width(600)
{

}

CGenerateDialog::~CGenerateDialog()
{
}

void CGenerateDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CLUSTERS, m_clusters);
	DDX_Text(pDX, IDC_HEIGHT, m_height);
	DDX_Text(pDX, IDC_POINTS, m_points);
	DDX_Text(pDX, IDC_WIDTH, m_width);
}


BEGIN_MESSAGE_MAP(CGenerateDialog, CDialog)
END_MESSAGE_MAP()


// CGenerateDialog message handlers
