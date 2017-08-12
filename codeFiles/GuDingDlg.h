#pragma once


// GuDingDlg dialog

class GuDingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(GuDingDlg)

public:
	GuDingDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~GuDingDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int m_YuZhi;
	bool ifok;
	afx_msg void OnBnClickedOk();
	int GetYuZhi();
};
