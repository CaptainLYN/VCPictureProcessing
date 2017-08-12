// ZheXianDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MfcPictureProcessing.h"
#include "ZheXianDlg.h"
#include "afxdialogex.h"


// ZheXianDlg dialog

IMPLEMENT_DYNAMIC(ZheXianDlg, CDialogEx)

ZheXianDlg::ZheXianDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(ZheXianDlg::IDD, pParent)
	, X1(0)
	, X2(0)
	, Y1(0)
	, Y2(0)
{
	ifok=false;
}

ZheXianDlg::~ZheXianDlg()
{
}

void ZheXianDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, X1);
	DDV_MinMaxInt(pDX, X1, 0, 255);
	DDX_Text(pDX, IDC_EDIT2, X2);
	DDV_MinMaxInt(pDX, X2, 0, 255);
	DDX_Text(pDX, IDC_EDIT3, Y1);
	DDV_MinMaxInt(pDX, Y1, 0, 255);
	DDX_Text(pDX, IDC_EDIT4, Y2);
	DDV_MinMaxInt(pDX, Y2, 0, 255);
}


BEGIN_MESSAGE_MAP(ZheXianDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &ZheXianDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// ZheXianDlg message handlers


void ZheXianDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	UpdateData(false);
	ifok=true;
	CDialogEx::OnOK();
}
int ZheXianDlg::GetX1()
{
	return X1;
}
int ZheXianDlg::GetY1()
{
	return Y1;
}
int ZheXianDlg::GetX2()
{
	return X2;
}
int ZheXianDlg::GetY2()
{
	return Y2;
}