#pragma once


// ShuangYuZhiDlg dialog

class ShuangYuZhiDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ShuangYuZhiDlg)

public:
	ShuangYuZhiDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~ShuangYuZhiDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG4 };
    int GetLow();
	int GetHigh();
	int GetMode();
	bool ifok;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	
	DECLARE_MESSAGE_MAP()
private:
	int low;
	int high;
	int mode;
public:
	afx_msg void OnBnClickedOk();
private:
	CString modeString;
};
