// XuanZhuanDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MfcPictureProcessing.h"
#include "XuanZhuanDlg.h"
#include "afxdialogex.h"


// XuanZhuanDlg dialog

IMPLEMENT_DYNAMIC(XuanZhuanDlg, CDialogEx)

XuanZhuanDlg::XuanZhuanDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(XuanZhuanDlg::IDD, pParent)
	, angle(0)
{
	ifok=false;
}

XuanZhuanDlg::~XuanZhuanDlg()
{
}

void XuanZhuanDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, angle);
}


BEGIN_MESSAGE_MAP(XuanZhuanDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &XuanZhuanDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// XuanZhuanDlg message handlers


void XuanZhuanDlg::OnBnClickedOk()
{
	ifok=true;
	UpdateData(true);
	UpdateData(false);
	CDialogEx::OnOK();
}
double XuanZhuanDlg::GetAngle()
{
	return angle;
}
