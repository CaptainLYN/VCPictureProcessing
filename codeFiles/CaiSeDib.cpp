#include "StdAfx.h"
#include "CaiSeDib.h"
#include<Windowsx.h>
#include"CDib.h"
#define _USE_MATH_DEFINES
#include<cmath>
CaiSeDib::CaiSeDib(void)
{
}
CaiSeDib::~CaiSeDib(void)
{
}
void CaiSeDib::GetDib(CDib *d)
{
	dib=d;
}
void CaiSeDib::MaxGray()
{
	int height=dib->GetHeight();
	int lbs=dib->GetDibWidthBytes();;
	LPBYTE p_data=dib->GetData();
	BYTE blue,green,red,gray;
	for(int j=0;j<height;j++)
		for(int i=0;i<lbs;i+=3)//这里一定要写lbs，否则宽度只有原来的1/3
		{
			blue=p_data[lbs*j+i];
			green=p_data[lbs*j+i+1];
			red=p_data[lbs*j+i+2];
			gray=blue;
			if(red>blue)
				gray=red;
			if(green>gray)
					gray=green;
			p_data[lbs*j+i]=gray;
			p_data[lbs*j+i+1]=gray;
			p_data[lbs*j+i+2]=gray;
		}
}
void CaiSeDib::GongShiGray()
{
	int height=dib->GetHeight();
	int lbs=dib->GetDibWidthBytes();;
	LPBYTE p_data=dib->GetData();
	BYTE blue,green,red,gray;
	for(int j=0;j<height;j++)
		for(int i=0;i<lbs;i+=3)//这里一定要写lbs，否则宽度只有原来的1/3
		{
			blue=p_data[lbs*j+i];
			green=p_data[lbs*j+i+1];
			red=p_data[lbs*j+i+2];
			gray=red*0.3+green*0.59+blue*0.11;
			p_data[lbs*j+i]=gray;
			p_data[lbs*j+i+1]=gray;
			p_data[lbs*j+i+2]=gray;
		}
}
void CaiSeDib::PaintColor(int m_red,int m_green,int m_blue)
{
	int lbs=dib->GetDibWidthBytes();
	int height=dib->GetHeight();
	LPBYTE p_data=dib->GetData();
	BYTE blue,green,red,gray;
	for(int j=0;j<height;j++)
		for(int i=0;i<lbs;i+=3)
		{
			blue=p_data[j*lbs+i];
			green=p_data[j*lbs+i+1];
			red=p_data[j*lbs+i+2];
			gray=red*0.3+green*0.59+blue*0.11;
			p_data[j*lbs+i]=m_blue*gray*1.0/255;
			p_data[j*lbs+i+1]=m_green*gray*1.0/255;
			p_data[j*lbs+i+2]=m_red*gray*1.0/255;
		}
}
void CaiSeDib::LightAlter(int m_light)
{
	int lbs=dib->GetDibWidthBytes();
	int height=dib->GetHeight();
	LPBYTE p_data=dib->GetData();
	int a;
	for(int j=0;j<height;j++)
		for(int i=0;i<lbs;i+=3)
		{
			a=p_data[j*lbs+i]*m_light*1.0/100;
			p_data[j*lbs+i]=a;
			if(a<0)
				p_data[j*lbs+i]=0;
			if(a>255)
				p_data[j*lbs+i]=255;
		}
}
void CaiSeDib::ContrastAlter(int m_increment)
{
	int nHigh=255-m_increment;
	//对于极端情况加以处理
	if(nHigh<m_increment)
	{
		nHigh=127;
		m_increment=120;
	}
	if(m_increment<-127) m_increment=-120;
	//扩展或者压缩区间的长度
	int nStretch=255;
	if(m_increment>=0)
		nStretch=255-2*m_increment;
	else
		nStretch=255+2*m_increment;
	BYTE *p_data=dib->GetData();
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	int lbs=dib->GetDibWidthBytes();
	LPBYTE red,green,blue;
	if(m_increment>=0)
	{
		for(int j=0;j<height;j++)
			for(int i=0;i<lbs;i+=3)
			{
				//调整蓝色
				blue=p_data+j*lbs+i;
				if(*blue<=m_increment)
					*blue=0;
				else if(*blue>nHigh)
					*blue=255;
				else
					*blue=((*blue-m_increment)*255)*1.0/nStretch;
				//调整绿色
				green=p_data+j*lbs+i+1;
				if(*green<=m_increment)
					*green=0;
				else if(*green>nHigh)
					*green=255;
				else
					*green=((*green-m_increment)*255)*1.0/nStretch;
				//调整红色
				red=p_data+j*lbs+i+2;
				if(*red<=m_increment)
					*red=0;
				else if(*red>nHigh)
					*red=255;
				else
					*red=((*red-m_increment)*255)*1.0/nStretch;
			}
	}
	else//m_increment<0的时候
	{
		for(int j=0;j<height;j++)
			for(int i=0;i<lbs;i+=3)
			{
				blue=p_data+j*lbs+i;
				*blue=((*blue)*nStretch)*1.0/255-m_increment;
				green=p_data+j*lbs+i+1;
				*green=((*green)*nStretch)*1.0/255-m_increment;
				red=p_data+j*lbs+i+2;
				*red=((*red)*nStretch)*1.0/255-m_increment;
			}
	}
}
void CaiSeDib::LightReverse()
{
	int lbs=dib->GetDibWidthBytes();
	int height=dib->GetHeight();
	LPBYTE p_data=dib->GetData();
	int a;
	for(int j=0;j<height;j++)
		for(int i=0;i<lbs;i++)
		{
				a=p_data[j*lbs+i];
				p_data[j*lbs+i]=255-a;
		}
}
void CaiSeDib::Exposal()
{
	int lbs=dib->GetDibWidthBytes();
	int height=dib->GetHeight();
	LPBYTE p_data=dib->GetData();
	int a;
	for(int j=0;j<height;j++)
		for(int i=0;i<lbs;i++)
		{
			if(p_data[j*lbs+i]<128)
				p_data[j*lbs+i]=255-p_data[j*lbs+i];
		}
}
void CaiSeDib::Spread()
{
	int lbs=dib->GetDibWidthBytes();
	int height=dib->GetHeight();
	LPBYTE p_data=dib->GetData();
	LPBYTE temp=new BYTE[lbs*height];
	memcpy(temp,p_data,sizeof(BYTE)*height*lbs);
	int m,n,blue,green,red;
	srand((unsigned)time(NULL));
	for(int j=2;j<height-2;j++)
		for(int i=6;i<lbs-6;i+=3)//按照书上的原理，但是代码是不一样的
		{
			m=rand()%5-2;//行随机数
			n=rand()%5-2;//列随机数
			blue=p_data[(j+m)*lbs+i+n*3];
			green=p_data[(j+m)*lbs+i+n*3+1];
			red=p_data[(j+m)*lbs+i+n*3+2];
			temp[j*lbs+i]=blue;
			temp[j*lbs+i+1]=green;
			temp[j*lbs+i+2]=red;
		}
	memcpy(p_data,temp,sizeof(BYTE)*lbs*height);
	delete[]temp;
}
void CaiSeDib::Mosaic()
{
	int lbs=dib->GetDibWidthBytes();
	int height=dib->GetHeight();
	LPBYTE p_data=dib->GetData();
	LPBYTE temp=new BYTE[lbs*height];
	memcpy(temp,p_data,sizeof(BYTE)*height*lbs);
	int m,n,blue,green,red;
	
	for(int j=2;j<height-2;j++)
		for(int i=6;i<lbs-6;i+=15)//按照书上的原理，但是代码是不一样的;这里i要加15但是不是3
		{
			//对周围的蓝色求平均值
			blue=0;
			for(int m=-2;m<=2;m++)
				for(int n=-6;n<=6;n+=3)
				{
					blue+=p_data[(j+m)*lbs+i+n];
				}
			blue=blue*1.0/25;
			for(int m=-2;m<=2;m++)
				for(int n=-6;n<=6;n+=3)
				{
					temp[(j+m)*lbs+i+n]=blue;
				}
			//对周围的绿色求平均值
			green=0;
			for(int m=-2;m<=2;m++)
				for(int n=-6;n<=6;n+=3)
				{
					green+=p_data[(j+m)*lbs+i+n+1];
				}
			green=green*1.0/25;
			for(int m=-2;m<=2;m++)
				for(int n=-6;n<=6;n+=3)
				{
					temp[(j+m)*lbs+i+n+1]=green;
				}
			//对周围的红色求平均值
			red=0;
			for(int m=-2;m<=2;m++)
				for(int n=-6;n<=6;n+=3)
				{
					red+=p_data[(j+m)*lbs+i+n+2];
				}
			red=red*1.0/25;
			for(int m=-2;m<=2;m++)
				for(int n=-6;n<=6;n+=3)
				{
					temp[(j+m)*lbs+i+n+2]=red;
				}
		}
	memcpy(p_data,temp,sizeof(BYTE)*lbs*height);
	delete[]temp;
}
void CaiSeDib::Smoothness()
{
	int lbs=dib->GetDibWidthBytes();
	int height=dib->GetHeight();
	LPBYTE p_data=dib->GetData();
	LPBYTE temp=new BYTE[lbs*height];
	memcpy(temp,p_data,sizeof(BYTE)*lbs*height);
	int data;
	for(int j=1;j<height-1;j++)
		for(int i=3;i<lbs-3;i++)
		{
			data=p_data[(j-1)*lbs+i-3]+p_data[(j-1)*lbs+i]+p_data[(j-1)*lbs+i+3]
			    +p_data[j*lbs+i-3]+p_data[j*lbs+i]+p_data[j*lbs+i+3]+
					p_data[(j+1)*lbs+i-3]+p_data[(j+1)*lbs+i]+p_data[(j+1)*lbs+i+3];
				temp[j*lbs+i]=data*1.0/9;
		}
	memcpy(p_data,temp,sizeof(BYTE)*height*lbs);
	delete[]temp;
}
void CaiSeDib::Lowlvbo3()
{
	int lbs=dib->GetDibWidthBytes();
	int height=dib->GetHeight();
	LPBYTE p_data=dib->GetData();
	LPBYTE temp=new BYTE[lbs*height];
	memcpy(temp,p_data,sizeof(BYTE)*lbs*height);
	int data;
	double h[3][3]={0.1,0.1,0.1,0.1,0.2,0.1,0.1,0.1,0.1};
	for(int j=1;j<height-1;j++)
		for(int i=3;i<lbs-3;i++)
		{
			data=h[0][0]*p_data[(j-1)*lbs+i-3]+h[0][1]*p_data[(j-1)*lbs+i]+h[0][2]*p_data[(j-1)*lbs+i+3]
			    +h[1][0]*p_data[j*lbs+i-3]+h[1][1]*p_data[j*lbs+i]+h[1][2]*p_data[j*lbs+i+3]+
					h[2][0]*p_data[(j+1)*lbs+i-3]+h[2][1]*p_data[(j+1)*lbs+i]+h[2][2]*p_data[(j+1)*lbs+i+3];
				temp[j*lbs+i]=data;
		}
	memcpy(p_data,temp,sizeof(BYTE)*height*lbs);
	delete[]temp;
}
void CaiSeDib::Lowlvbo5()
{
	int lbs=dib->GetDibWidthBytes();
	int height=dib->GetHeight();
	LPBYTE p_data=dib->GetData();
	LPBYTE temp=new BYTE[lbs*height];
	memcpy(temp,p_data,sizeof(BYTE)*lbs*height);
	int data;
	int h[5][5]={1,1,1,1,1,
	             1,2,2,2,1,
	             1,2,3,2,1,
	             1,2,2,2,1,
	             1,1,1,1,1};
	for(int j=2;j<height-2;j++)
		for(int i=6;i<lbs-6;i++)
		{
			data=h[0][0]*p_data[(j-2)*lbs+i-6]+h[0][1]*p_data[(j-2)*lbs+i-3]+h[0][2]*p_data[(j-2)*lbs+i]+h[0][3]*p_data[(j-2)*lbs+i+3]+h[0][4]*p_data[(j-2)*lbs+i+6]
			    +h[1][0]*p_data[(j-1)*lbs+i-6]+h[1][1]*p_data[(j-1)*lbs+i-3]+h[1][2]*p_data[(j-1)*lbs+i]+h[1][3]*p_data[(j-1)*lbs+i+3]+h[1][4]*p_data[(j-1)*lbs+i+6]
				+h[2][0]*p_data[j*lbs+i-6]+h[2][1]*p_data[j*lbs+i-3]+h[2][2]*p_data[j*lbs+i]+h[2][3]*p_data[j*lbs+i+3]+h[2][4]*p_data[j*lbs+i+6]
				+h[3][0]*p_data[(j+1)*lbs+i-6]+h[3][1]*p_data[(j+1)*lbs+i-3]+h[3][2]*p_data[(j+1)*lbs+i]+h[3][3]*p_data[(j+1)*lbs+i+3]+h[3][4]*p_data[(j+1)*lbs+i+6]
				+h[4][0]*p_data[(j+2)*lbs+i-6]+h[4][1]*p_data[(j+2)*lbs+i-3]+h[4][2]*p_data[(j+2)*lbs+i]+h[4][3]*p_data[(j+2)*lbs+i+3]+h[4][4]*p_data[(j+1)*lbs+i+6];
				temp[j*lbs+i]=data*1.0/35;
		}
	memcpy(p_data,temp,sizeof(BYTE)*height*lbs);
	delete[]temp;
}
void CaiSeDib::ShuiPingGrow()
{
	int lbs=dib->GetDibWidthBytes();
	int height=dib->GetHeight();
	LPBYTE p_data=dib->GetData();
	LPBYTE temp=new BYTE[lbs*height];
	//memcpy(temp,p_data,sizeof(BYTE)*lbs*height);
	memset(temp,0,sizeof(BYTE)*height*lbs);
	int data;
	int h[1][3]={-1,2,-1};
	for(int j=0;j<height;j++)
		for(int i=3;i<lbs-3;i++)
		{
			data=h[0][0]*p_data[j*lbs+i-3]+h[0][1]*p_data[j*lbs+i]+h[0][2]*p_data[j*lbs+i+3];
			if(data>20)
				temp[j*lbs+i]=data+100;//让亮度值低的依旧低，亮的更亮，高通滤波器
			else
				temp[j*lbs+i]=data;
		}
	memcpy(p_data,temp,sizeof(BYTE)*height*lbs);
	delete[]temp;
}
void CaiSeDib::ChuiZhiGrow()
{
	int lbs=dib->GetDibWidthBytes();
	int height=dib->GetHeight();
	LPBYTE p_data=dib->GetData();
	LPBYTE temp=new BYTE[lbs*height];
	//memcpy(temp,p_data,sizeof(BYTE)*lbs*height);
	memset(temp,0,sizeof(BYTE)*height*lbs);
	int data;
	int h[1][3]={-1,2,-1};
	for(int j=1;j<height-1;j++)
		for(int i=0;i<lbs;i++)
		{
			data=h[0][0]*p_data[(j-1)*lbs+i]+h[0][1]*p_data[j*lbs+i]+h[0][2]*p_data[(j+1)*lbs+i];
			if(data>20)
				temp[j*lbs+i]=data+100;
			else
				temp[j*lbs+i]=data;
		}
	memcpy(p_data,temp,sizeof(BYTE)*height*lbs);
	delete[]temp;
}
void CaiSeDib::ShuangXiangGrow()
{
	int lbs=dib->GetDibWidthBytes();
	int height=dib->GetHeight();
	LPBYTE p_data=dib->GetData();
	LPBYTE temp=new BYTE[lbs*height];
	//memcpy(temp,p_data,sizeof(BYTE)*lbs*height);
	memset(temp,0,sizeof(BYTE)*height*lbs);
	int data;
	int h[3][3]={-1,-1,-1,-1,8,-1,-1,-1,-1};
	for(int j=1;j<height-1;j++)
		for(int i=3;i<lbs-3;i++)
		{
			data=h[0][0]*p_data[(j-1)*lbs+i-3]+h[0][1]*p_data[(j-1)*lbs+i]+h[0][2]*p_data[(j-1)*lbs+i+3]+
				h[1][0]*p_data[j*lbs+i-3]+h[1][1]*p_data[j*lbs+i]+h[1][2]*p_data[j*lbs+i+3]+
				h[2][0]*p_data[(j+1)*lbs+i-3]+h[2][1]*p_data[j*lbs+i]+h[2][2]*p_data[(j+1)*lbs+i+3];
			if(data>20)
				temp[j*lbs+i]=data+100;
			else
				temp[j*lbs+i]=data;
		}
	memcpy(p_data,temp,sizeof(BYTE)*height*lbs);
	delete[]temp;
}
void CaiSeDib::Sharp()
{
	int lbs=dib->GetDibWidthBytes();
	int height=dib->GetHeight();
	LPBYTE p_data=dib->GetData();
	LPBYTE temp=new BYTE[lbs*height];
	memset(temp,0,sizeof(BYTE)*height*lbs);
	int data;
	for(int j=1;j<height;j++)
		for(int i=1;i<lbs;i++)
		{
			data=(p_data[j*lbs+i]-p_data[lbs*(j-1)+i-1])*1.0/4;
			if(data+p_data[j*lbs+i]>255)
				temp[j*lbs+i]=255;
			else
				temp[j*lbs+i]=data+p_data[j*lbs+i];
		}
	memcpy(p_data,temp,sizeof(BYTE)*lbs*height);
	delete[]temp;
}
void CaiSeDib::Gaotonglvbo(int m_GaoTong)
{
	int lbs=dib->GetDibWidthBytes();
	int height=dib->GetHeight();
	LPBYTE p_data=dib->GetData();
	LPBYTE temp=new BYTE[lbs*height];
	
	memset(temp,0,sizeof(BYTE)*height*lbs);
	int data;
	int h[3][3];
	if(m_GaoTong==1)//基本高通，给自己很大的5，两边的低通也赋差不多的值，斜对角那些也加入自己
	{
		h[0][0]=1;
		h[0][1]=-2;
		h[0][2]=1;
		h[1][0]=-2;
		h[1][1]=5;//如果中间分别变成4和8，就跟轮廓提取差不多了
		h[1][2]=-2;
		h[2][0]=1;
		h[2][1]=-2;
		h[2][2]=1;
	}
	else if(m_GaoTong==2)//就自己一个，然后跟周围4个比较
	{
		h[0][0]=0;
		h[0][1]=-1;
		h[0][2]=0;
		h[1][0]=-1;
		h[1][1]=5;
		h[1][2]=-1;
		h[2][0]=0;
		h[2][1]=-1;
		h[2][2]=0;
	}
	else//自己一个跟周围9个比较，狂妄自大
	{
		h[0][0]=-1;
		h[0][1]=-1;
		h[0][2]=-1;
		h[1][0]=-1;
		h[1][1]=9;
		h[1][2]=-1;
		h[2][0]=-1;
		h[2][1]=-1;
		h[2][2]=-1;
	}
	for(int j=1;j<height-1;j++)
		for(int i=3;i<lbs-3;i++)
		{
			data=h[0][0]*p_data[(j-1)*lbs+i-3]+h[0][1]*p_data[(j-1)*lbs+i]+h[0][2]*p_data[(j-1)*lbs+i+3]+
				h[1][0]*p_data[j*lbs+i-3]+h[1][1]*p_data[j*lbs+i]+h[1][2]*p_data[j*lbs+i+3]+
				h[2][0]*p_data[(j+1)*lbs+i-3]+h[2][1]*p_data[j*lbs+i]+h[2][2]*p_data[(j+1)*lbs+i+3];
			if(data>255)
				temp[j*lbs+i]=255;
			else
				temp[j*lbs+i]=data;
		}
	memcpy(p_data,temp,sizeof(BYTE)*height*lbs);
	delete[]temp;
}
void CaiSeDib::FuDiao()
{
	int lbs=dib->GetDibWidthBytes();
	int height=dib->GetHeight();
	LPBYTE p_data=dib->GetData();
	LPBYTE temp=new BYTE[lbs*height];
	memset(temp,0,sizeof(BYTE)*height*lbs);
	int data;
	for(int j=0;j<height;j++)
		for(int i=3;i<lbs;i++)
		{
			data=p_data[j*lbs+i]-p_data[j*lbs+i-3]+128;
			if(data>255)
				temp[j*lbs+i]=255;
			else if(data<0)
				temp[j*lbs+i]=0;
			else
				temp[j*lbs+i]=data;
		}
	memcpy(p_data,temp,sizeof(BYTE)*height*lbs);
	delete[]temp;
}
void CaiSeDib::NiHong()
{
	int lbs=dib->GetDibWidthBytes();
	int height=dib->GetHeight();
	LPBYTE p_data=dib->GetData();
	LPBYTE temp=new BYTE[lbs*height];
	memset(temp,0,sizeof(BYTE)*height*lbs);
	int data;
	for(int j=1;j<height;j++)
		for(int i=0;i<lbs-3;i++)
		{
			data=2*sqrt(pow((double)(p_data[j*lbs+i]-p_data[j*lbs+i-3]),2)+pow((double)(p_data[j*lbs+i]-p_data[(j-1)*lbs+i]),2));
			if(data>255)
				temp[j*lbs+i]=255;
			else if(data<0)
				temp[j*lbs+i]=0;
			else
				temp[j*lbs+i]=data;
		}
	memcpy(p_data,temp,sizeof(BYTE)*height*lbs);
	delete[]temp;
}