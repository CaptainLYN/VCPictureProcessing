#pragma once


// ZheXianDlg dialog

class ZheXianDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ZheXianDlg)

public:
	ZheXianDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~ZheXianDlg();
	bool ifok;
	int GetX1();
	int GetX2();
	int GetY1();
	int GetY2();
// Dialog Data
	enum { IDD = IDD_DIALOG6 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	int X1;
	int X2;
	int Y1;
	int Y2;
public:
	afx_msg void OnBnClickedOk();
};
