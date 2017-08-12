#pragma once


// ChuangkouDlg dialog

class ChuangkouDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ChuangkouDlg)

public:
	ChuangkouDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~ChuangkouDlg();
	bool ifok;
	int GetLow();
	int GetHigh();

// Dialog Data
	enum { IDD = IDD_DIALOG5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	int low;
	int high;
public:
	afx_msg void OnBnClickedOk();
};
