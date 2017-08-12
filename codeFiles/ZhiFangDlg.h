#pragma once


// ZhiFangDlg dialog

class ZhiFangDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ZhiFangDlg)

public:
	ZhiFangDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~ZhiFangDlg();
	void OnPaint();
	void SetData(float* data);

// Dialog Data
	enum { IDD = 139 };//这里总是出问题，所以直接写成数字了

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	float *data;
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
