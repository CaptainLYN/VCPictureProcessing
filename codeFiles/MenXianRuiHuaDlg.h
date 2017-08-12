#pragma once


// MenXianRuiHuaDlg dialog

class MenXianRuiHuaDlg : public CDialogEx
{
	DECLARE_DYNAMIC(MenXianRuiHuaDlg)

public:
	MenXianRuiHuaDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~MenXianRuiHuaDlg();
	bool ifok;
	byte GetMenXian();

// Dialog Data
	enum { IDD = IDD_DIALOG8 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	BYTE menxian;
public:
	afx_msg void OnBnClickedOk();
};
