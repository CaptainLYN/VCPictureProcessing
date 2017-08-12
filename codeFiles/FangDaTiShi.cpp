// FangDaTiShi.cpp : implementation file
//

#include "stdafx.h"
#include "MfcPictureProcessing.h"
#include "FangDaTiShi.h"
#include "afxdialogex.h"


// FangDaTiShi dialog

IMPLEMENT_DYNAMIC(FangDaTiShi, CDialogEx)

FangDaTiShi::FangDaTiShi(CWnd* pParent /*=NULL*/)
	: CDialogEx(FangDaTiShi::IDD, pParent)
	, xzoom(0)
	, yzoom(0)
{
	ifok=0;
}

FangDaTiShi::~FangDaTiShi()
{
}

void FangDaTiShi::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, xzoom);
	DDX_Text(pDX, IDC_EDIT3, yzoom);
}


BEGIN_MESSAGE_MAP(FangDaTiShi, CDialogEx)
	ON_BN_CLICKED(IDOK, &FangDaTiShi::OnBnClickedOk)
END_MESSAGE_MAP()


// FangDaTiShi message handlers


void FangDaTiShi::OnBnClickedOk()
{
	UpdateData(true);
	UpdateData(false);
	ifok=1;
	CDialogEx::OnOK();
}
float FangDaTiShi::Getx()
{
	return xzoom;
}
float FangDaTiShi::Gety()
{
	return yzoom;
}