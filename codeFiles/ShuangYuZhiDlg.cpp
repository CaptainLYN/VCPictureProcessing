// ShuangYuZhiDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MfcPictureProcessing.h"
#include "ShuangYuZhiDlg.h"
#include "afxdialogex.h"


// ShuangYuZhiDlg dialog

IMPLEMENT_DYNAMIC(ShuangYuZhiDlg, CDialogEx)

ShuangYuZhiDlg::ShuangYuZhiDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(ShuangYuZhiDlg::IDD, pParent)
	, low(0)
	, high(0)
	, modeString(_T(""))
{
	ifok=false;
	mode=0;
}

ShuangYuZhiDlg::~ShuangYuZhiDlg()
{
}

void ShuangYuZhiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, low);
	DDX_Text(pDX, IDC_EDIT2, high);
	DDX_CBString(pDX, IDC_COMBO1, modeString);
}


BEGIN_MESSAGE_MAP(ShuangYuZhiDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &ShuangYuZhiDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// ShuangYuZhiDlg message handlers


void ShuangYuZhiDlg::OnBnClickedOk()
{
	UpdateData(true);
	UpdateData(false);
	if(modeString.Compare(_T("0-255-0"))==0)
		mode=0;
	else if(modeString.Compare(_T("255-0-255"))==0)
		mode=1;
	else
		{
			MessageBox(_T("请选择模式:)"),_T("提示"),MB_OK);
			return;
	}
	ifok=true;
	CDialogEx::OnOK();
}
int ShuangYuZhiDlg::GetLow()
{
	return low;
}
int ShuangYuZhiDlg::GetHigh()
{
	return high;
}
int ShuangYuZhiDlg::GetMode()
{
	return mode;
}