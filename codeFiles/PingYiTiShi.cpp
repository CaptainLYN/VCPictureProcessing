// PingYiTiShi.cpp : implementation file
//

#include "stdafx.h"
#include "MfcPictureProcessing.h"
#include "PingYiTiShi.h"
#include "afxdialogex.h"


// PingYiTiShi dialog

IMPLEMENT_DYNAMIC(PingYiTiShi, CDialogEx)

PingYiTiShi::PingYiTiShi(CWnd* pParent /*=NULL*/)
	: CDialogEx(PingYiTiShi::IDD, pParent)
	, m_Xmove(0)
	, m_Ymove(0)
{
	ifok=0;
}

PingYiTiShi::~PingYiTiShi()
{
}

void PingYiTiShi::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Xmove);
	DDX_Text(pDX, IDC_EDIT2, m_Ymove);
}


BEGIN_MESSAGE_MAP(PingYiTiShi, CDialogEx)
	ON_BN_CLICKED(IDOK, &PingYiTiShi::OnBnClickedOk)
END_MESSAGE_MAP()


// PingYiTiShi message handlers


void PingYiTiShi::OnBnClickedOk()//点击确认后
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	UpdateData(false);
	ifok=1;
	CDialogEx::OnOK();
	
}
int PingYiTiShi::GetX()
{
	return m_Xmove;
}
int PingYiTiShi::GetY()
{
	return m_Ymove;
}