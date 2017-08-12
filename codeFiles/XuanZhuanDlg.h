#pragma once


// XuanZhuanDlg dialog

class XuanZhuanDlg : public CDialogEx
{
	DECLARE_DYNAMIC(XuanZhuanDlg)

public:
	XuanZhuanDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~XuanZhuanDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	double angle;
	bool ifok;
	afx_msg void OnBnClickedOk();
	double GetAngle();
};
