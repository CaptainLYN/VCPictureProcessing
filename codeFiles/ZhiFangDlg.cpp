// ZhiFangDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MfcPictureProcessing.h"
#include "ZhiFangDlg.h"
#include "afxdialogex.h"


// ZhiFangDlg dialog

IMPLEMENT_DYNAMIC(ZhiFangDlg, CDialogEx)

ZhiFangDlg::ZhiFangDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(ZhiFangDlg::IDD, pParent)
{
	data=NULL;
}

ZhiFangDlg::~ZhiFangDlg()
{
}

void ZhiFangDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ZhiFangDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &ZhiFangDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// ZhiFangDlg message handlers
void ZhiFangDlg::SetData(float *d)
{
	data=d;
}
void ZhiFangDlg::OnPaint()
{
	//
	//CPaintDC dc(this);//用这个画不出来
	CDC *dc=GetDC();
	CPen* pPen=new CPen;//创建画笔
	pPen->CreatePen(PS_SOLID,1,RGB(0,0,0));//创建一支黑笔
	CGdiObject *pOldPen=dc->SelectObject(pPen);//选中新画笔，保存旧画笔
	int i=0;
	CString str;
	CPoint OPos(14,188),NowPos;//绘制坐标系
	//绘制X坐标轴
	dc->MoveTo(OPos);
	NowPos.x=284;
	NowPos.y=188;
	dc->LineTo(NowPos);
	//绘制箭头
	dc->LineTo(279,183);
	dc->MoveTo(NowPos);
	dc->LineTo(279,193);
	//绘制x轴坐标系数
	//下面单独挑出来是为了好看
	i=0;
	dc->MoveTo(OPos.x+i,OPos.y);
	dc->LineTo(CPoint(OPos.x+i,OPos.y+5));
	str.Format(_T("%d"),i);
	dc->TextOutW(OPos.x+i-5,OPos.y+7,str);
	for(i=10;i<256;i+=10)//这里有修改
	{
		if(i%10==0)//绘制竖杠
		{
			dc->MoveTo(OPos.x+i,OPos.y);
			dc->LineTo(CPoint(OPos.x+i,OPos.y+5));
		}
		if(i%40==0)//绘制字
		{
			str.Format(_T("%d"),i);
			dc->TextOutW(OPos.x+i-10,OPos.y+7,str);
		}
	}
	//绘制y轴坐标系数
	dc->MoveTo(OPos);
	NowPos.x=OPos.x;
	NowPos.y=4;
	dc->LineTo(NowPos);
	//绘制箭头
	dc->LineTo(NowPos.x-5,NowPos.y+5);//画笔最后停在哪里，绘制的中心就在哪里
	dc->MoveTo(NowPos);
	dc->LineTo(NowPos.x+5,NowPos.y+5);
	//寻找数组最大的数据
	float max=0;
	for(i=0;i<256;i++)
	{
		if(max<data[i])
			max=data[i];
	}
	//y轴坐标系数的数据步长
	//float Tstep=max/10;
	//y轴坐标系数的刻度步长
	float Ystep=174/20;
	//显示y坐标的刻度和数据
	i=20;
	dc->MoveTo(OPos.x,OPos.y-Ystep*i);
	dc->LineTo(OPos.x+5,OPos.y-Ystep*i);
	str.Format(_T("%f"),max);//这里修改了
	dc->TextOutW(20,OPos.y-Ystep*i-20,str);	
	
	//绘制灰度直方图
	for(i=0;i<256;i++)
	{
		NowPos.x=OPos.x+i;
		NowPos.y=OPos.y;
		dc->MoveTo(NowPos);
		NowPos.y=187-20*Ystep*data[i]/max;//计算比例，用20*Ystep，不能用175，因为中间精度缺失了太多
		dc->LineTo(NowPos);
	}
	dc->SelectObject(pOldPen);

	delete pPen;
	//Invalidate();
}

void ZhiFangDlg::OnBnClickedButton1()
{
	if(data!=NULL)
		OnPaint();
}
