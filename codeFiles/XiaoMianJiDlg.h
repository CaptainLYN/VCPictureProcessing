#pragma once


// XiaoMianJiDlg 对话框

class XiaoMianJiDlg : public CDialogEx
{
	DECLARE_DYNAMIC(XiaoMianJiDlg)

public:
	XiaoMianJiDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~XiaoMianJiDlg();
	bool ifok;

// 对话框数据
	enum { IDD = IDD_DIALOG9 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	int mianji;
public:
	afx_msg void OnBnClickedOk();
	int GetMianJi();
};
