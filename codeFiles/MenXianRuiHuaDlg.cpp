// MenXianRuiHuaDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MfcPictureProcessing.h"
#include "MenXianRuiHuaDlg.h"
#include "afxdialogex.h"


// MenXianRuiHuaDlg dialog

IMPLEMENT_DYNAMIC(MenXianRuiHuaDlg, CDialogEx)

MenXianRuiHuaDlg::MenXianRuiHuaDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(MenXianRuiHuaDlg::IDD, pParent)
	, menxian(0)
{
	ifok=false;
}

MenXianRuiHuaDlg::~MenXianRuiHuaDlg()
{
}

void MenXianRuiHuaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, menxian);
	DDV_MinMaxByte(pDX, menxian, 0, 255);
}


BEGIN_MESSAGE_MAP(MenXianRuiHuaDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &MenXianRuiHuaDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// MenXianRuiHuaDlg message handlers
byte MenXianRuiHuaDlg::GetMenXian()
{
	return menxian;
}

void MenXianRuiHuaDlg::OnBnClickedOk()
{
	UpdateData(true);
	UpdateData(false);
	ifok=true;
	CDialogEx::OnOK();
}
