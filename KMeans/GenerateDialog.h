#pragma once


// CGenerateDialog dialog

class CGenerateDialog : public CDialog
{
	DECLARE_DYNAMIC(CGenerateDialog)

public:
	CGenerateDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CGenerateDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	UINT m_clusters;
	UINT m_height;
	UINT m_points;
	UINT m_width;
};
