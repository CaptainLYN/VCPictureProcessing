// nnZhongZhiDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MfcPictureProcessing.h"
#include "nnZhongZhiDlg.h"
#include "afxdialogex.h"


// nnZhongZhiDlg dialog

IMPLEMENT_DYNAMIC(nnZhongZhiDlg, CDialogEx)

nnZhongZhiDlg::nnZhongZhiDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(nnZhongZhiDlg::IDD, pParent)
	, size(0)
{
	ifok=false;
}

nnZhongZhiDlg::~nnZhongZhiDlg()
{
}

void nnZhongZhiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, size);
}


BEGIN_MESSAGE_MAP(nnZhongZhiDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &nnZhongZhiDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// nnZhongZhiDlg message handlers
int nnZhongZhiDlg::GetSize()
{
	return size;
}

void nnZhongZhiDlg::OnBnClickedOk()//确定按钮
{
	UpdateData(true);
	UpdateData(false);
	if(size>=3&&size%2==1)
	{
	ifok=true;
	CDialogEx::OnOK();
	}
	else
	{
		MessageBox(_T("窗口大小要为大于等于3的奇数！"),_T("提示"),MB_OK);
	}
}
