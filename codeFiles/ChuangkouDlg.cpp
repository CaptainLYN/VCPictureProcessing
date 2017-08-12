// ChuangkouDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MfcPictureProcessing.h"
#include "ChuangkouDlg.h"
#include "afxdialogex.h"


// ChuangkouDlg dialog

IMPLEMENT_DYNAMIC(ChuangkouDlg, CDialogEx)

ChuangkouDlg::ChuangkouDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(ChuangkouDlg::IDD, pParent)
	, low(0)
	, high(0)
{
	ifok=false;
}

ChuangkouDlg::~ChuangkouDlg()
{
}

void ChuangkouDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, low);
	DDX_Text(pDX, IDC_EDIT2, high);
}


BEGIN_MESSAGE_MAP(ChuangkouDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &ChuangkouDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// ChuangkouDlg message handlers
int ChuangkouDlg::GetLow()
{
	return low;
}
int ChuangkouDlg::GetHigh()
{
	return high;
}

void ChuangkouDlg::OnBnClickedOk()
{
	UpdateData(true);
	UpdateData(false);
	ifok=true;
	CDialogEx::OnOK();
}
