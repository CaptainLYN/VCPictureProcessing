#pragma once


// PingYiTiShi dialog

class PingYiTiShi : public CDialogEx
{
	DECLARE_DYNAMIC(PingYiTiShi)

public:
	PingYiTiShi(CWnd* pParent = NULL);   // standard constructor
	virtual ~PingYiTiShi();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int m_Xmove;
	int m_Ymove;
	int ifok;
	int GetX();
	int GetY();
	afx_msg void OnBnClickedOk();
};
