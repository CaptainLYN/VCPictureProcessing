#pragma once


// FangDaTiShi dialog

class FangDaTiShi : public CDialogEx
{
	DECLARE_DYNAMIC(FangDaTiShi)

public:
	FangDaTiShi(CWnd* pParent = NULL);   // standard constructor
	virtual ~FangDaTiShi();

// Dialog Data
	enum { IDD = IDD_Big };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	float xzoom;
	float yzoom;
	int ifok;
	afx_msg void OnBnClickedOk();
	float Getx();
	float Gety();
};
