// GuDingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MfcPictureProcessing.h"
#include "GuDingDlg.h"
#include "afxdialogex.h"


// GuDingDlg dialog

IMPLEMENT_DYNAMIC(GuDingDlg, CDialogEx)

GuDingDlg::GuDingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(GuDingDlg::IDD, pParent)
	, m_YuZhi(0)
{
	ifok=false;
}

GuDingDlg::~GuDingDlg()
{
}

void GuDingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_YuZhi);
}


BEGIN_MESSAGE_MAP(GuDingDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &GuDingDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// GuDingDlg message handlers


void GuDingDlg::OnBnClickedOk()
{
	UpdateData(true);
	ifok=true;
	UpdateData(false);
	CDialogEx::OnOK();
}
int GuDingDlg::GetYuZhi()
{
	return m_YuZhi;
}
