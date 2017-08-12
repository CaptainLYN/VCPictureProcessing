#pragma once


// nnZhongZhiDlg dialog

class nnZhongZhiDlg : public CDialogEx
{
	DECLARE_DYNAMIC(nnZhongZhiDlg)

public:
	nnZhongZhiDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~nnZhongZhiDlg();
	int GetSize();

// Dialog Data
	enum { IDD = IDD_DIALOG7 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	int size;
	
public:
	afx_msg void OnBnClickedOk();
	bool ifok;
};
