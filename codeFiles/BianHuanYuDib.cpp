#include "StdAfx.h"
//#include<WindowsX.h>
//#include<iostream>
//#include<stdio.h>
//#include<complex>
#define _USE_MATH_DEFINES
#include<math.h>

#include"CDib.h"

#include "BianHuanYuDib.h"


BianHuanYuDib::BianHuanYuDib(void)
{
}
BianHuanYuDib::~BianHuanYuDib(void)
{
}
void BianHuanYuDib::GetDib(CDib *d)
{
	dib=d;
}
void BianHuanYuDib::QFC(std::complex<double> *t,std::complex<double> *f,int r)
{
	long count;//傅里叶变换点数
	int i,j,k,p,bfsize;
	std::complex<double> *w,*x,*a,*b;
	double angle;//计算加权系数所用的角度值
	count=1<<r;//左移一位相当于乘以2
	//分配所需运算空间
	w=new std::complex<double> [count/2];
	a=new std::complex<double> [count];
	b=new std::complex<double> [count];
	for(i=0;i<count/2;i++)//系统计算
	{
		angle=-i*M_PI*2/count;
		w[i]=std::complex<double>(cos(angle),sin(angle));
	}
	memcpy(a,t,sizeof(std::complex<double>)*count);
	//采用频率分解法进行蝶形运算
	for(k=0;k<r;k++)
	{
		for(j=0;j<1<<k;j++)
		{
			bfsize=1<<(r-k);
			for(i=0;i<bfsize/2;i++)
			{
				p=j*bfsize;
				b[i+p]=a[i+p]+a[i+p+bfsize/2];
				b[i+p+bfsize/2]=(a[i+p]-a[i+p+bfsize/2])*w[i*(1<<k)];
			}
		}
		x=a;
		a=b;
		b=x;
	}
	//将乱序的变换序列重新排列
	for(j=0;j<count;j++)
	{
		p=0;
		for(i=0;i<r;i++)
		{
			if(j&(1<<i))
				p+=1<<(r-i-1);
		}
		f[j]=a[p];
	}
	delete[]w;
	delete[]a;
	delete[]b;
}
void BianHuanYuDib::FirstQuickFourier()
{
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	int lbs=dib->GetDibWidthBytes();
	LPBYTE p_data=dib->GetData(),p;
	long w=1,h=1;//进行傅里叶变换的宽度和高度（2的整数次方）
	int wp=0,hp=0;//迭代次数
	int i,j;
	double temp;//中间变量
	std::complex<double> *t,*f;
	while(w*2<=width)//计算进行傅里叶变换的宽度（2的整数次方)
	{
		w*=2;
		wp++;
	}
	while(h*2<=height)//计算进行傅里叶变换的高度（2的整数次方)
	{
		h*=2;
		hp++;
	}
	t=new std::complex<double>[lbs*height];//分配存储器空间
	f=new std::complex<double>[lbs*height];
	for(j=0;j<h;j++)
	{
		for(i=0;i<w;i++)
		{
			p=p_data+lbs*(height-j+1)+i;
			t[i+w*j]=std::complex<double>(*(p),0);
		}
	}
	for(j=0;j<h;j++)
		QFC(&t[w*j],&f[w*j],wp);
	for(j=0;j<h;j++)//转换变换结果
	{
		for(i=0;i<w;i++)
			t[j+h*i]=f[i+w*j];
	}
	for(j=0;j<w;j++)//水平方向进行快速傅里叶变换
		QFC(&t[j*h],&f[j*h],hp);
	for(j=0;j<h;j++)
		for(i=0;i<w;i++)
		{
			temp=sqrt(f[i*h+j].real()*f[i*h+j].real()+f[i*h+j].imag()*f[i*h+j].imag())/100;
			if(temp>255)
				temp=255;
			p=p_data+lbs*(height-(j<h/2?j+h/2:j-h/2)-1)+(i<w/2?i+w/2:i-w/2);//将变换后的原点移到中心，亮点在中间：平移后的傅里叶变换
			//p=p_data+lbs*(height-(j<h/2?j:j)-1)+(i<w/2?i:i);//如果是这个亮点在四周:平移前的傅里叶变换
			*(p)=(BYTE)temp;
		}
	delete[]t;
	delete[]f;
}
void BianHuanYuDib::LiSan(double *t,double *f,int r)
{
	long count;//离散余弦变换点数
	int i;//循环变量
	double dTemp;//中间变量
	std::complex<double> *x;
	count=1<<r;//计算离散余弦变换点数
	x=new std::complex<double>[count*2];
	//for(i=0;i<count*2;i++)
	//	x[i]=0;//赋初值为0
	for(i=0;i<count;i++)
		x[i]=t[i];
	QFC(x,x,r+1);//调用快速傅里叶函数
	dTemp=1/sqrt((double)count);
	f[0]=x[0].real()*dTemp;
	dTemp*=sqrt((double)2);
	for(i=1;i<count;i++)
	{
		f[i]=(x[i].real()*cos(i*M_PI/(count*2))+x[i].imag()+sin(i*M_PI/(count*2)))*dTemp;
	}
	delete[]x;
}
void BianHuanYuDib::DIBLiSanYuXian()
{
	LPBYTE p_data=dib->GetData();
	int height=dib->GetHeight();
	int width=dib->GetWidth();
	int i,j,w,h,wp,hp;
	double dTemp;
	int lbs=dib->GetDibWidthBytes();
	w=1;h=1;
	wp=0;
	hp=0;
	//计算进行离散余弦变换的高度和宽度（2的整数次方）
	while(w*2<=width)
	{
		w*=2;
		wp++;
	}
	while(h*2<=height)
	{
		h*=2;
		hp++;
	}
	//分配内存
	double *f=new double[lbs*height];
	double *F=new double[lbs*height];
	//行
	LPBYTE lpSrc;
	for(i=0;i<h;i++)
	{//列
		for(j=0;j<w;j++)
		{
			//指向DIB第i行，第j个像素的指针
			lpSrc=p_data+lbs*(height-1-i)+j;
			//给时域赋值
			f[j+i*w]=*(lpSrc);
		}
	}
	for(i=0;i<h;i++)
	{
		//对y方向进行离散余弦变换
		LiSan(&f[w*i],&F[w*i],wp);
	}
	//保存计算计算
	for(i=0;i<h;i++)
	{
		for(j=0;j<w;j++)
		{
			f[j*h+i]=F[j+w*i];
		}
	}
	for(j=0;j<w;j++)
	{
		LiSan(&f[j*h],&F[j*h],hp);
	}
	//行
	for(i=0;i<h;i++)
		for(j=0;j<w;j++)
		{
			//计算频谱
			dTemp=fabs(F[j*h+i]);
			//判断是否超过255
			if(dTemp>255)
				dTemp=255;
			//指向DIB第y行，第x个像素的指针
			lpSrc=p_data+lbs*(height-1-i)+j;
			//更新原图像
			*(lpSrc)=dTemp;
		}
	delete[]f;
	delete[]F;
}
void BianHuanYuDib::PerfectFilterL(int u,int v)
{
	LPBYTE p_data=dib->GetData(),p;
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	int lbs=dib->GetDibWidthBytes();
	double d0,max=0.0,*t,*h;//中间变量
	int i,j;
	t=new double[height*lbs*2+1];//分配存储器空间
	h=new double[height*lbs*2+1];
	std::complex<double> *f=new std::complex<double>[height*lbs*2+1];
	/*std::complex<double> *F=new std::complex<double>[height*lbs*2+1];*/

	d0=sqrt(double(u*u+v*v));
	for(j=0;j<height;j++)
		for(i=0;i<lbs;i++)
		{
			p=p_data+lbs*j+i;
			t[(2*lbs)*j+2*i+1]=*(p);//给时域赋值
			t[(2*lbs)*j+2*i+2]=0.0;
			if(sqrt(double(i*i+j*j))<=d0)
				h[2*i+(2*lbs)*j+1]=1.0;
			else
				h[2*i+(2*lbs)*j+1]=0.0;
			h[2*i+(2*lbs)*j+2]=0.0;
		}
	for(i=0;i<height*lbs*2+1;i++)
		f[i]=t[i];
	QFC(f,f,1);
	for(i=0;i<height*lbs*2+1;i++)
		t[i]=f[i].real();
		/*LiSan(t,t,1);*/
	for(j=1;j<height*lbs*2;j+=2)
	{
		t[j]=t[j]*h[j]-t[j+1]*h[j+1];
		t[j+1]=t[j]*h[j+1]+t[j+1]*h[j];
	}
	for(i=0;i<height*lbs*2+1;i++)
		f[i]=t[i];
	QFC(f,f,1);
	for(i=0;i<height*lbs*2+1;i++)
		t[i]=f[i].real();
	/*LiSan(t,t,-1);*/

	for(j=0;j<height;j++)
		for(i=0;i<lbs;i++)
		{
			t[(2*lbs)*j+2*i+1]=sqrt(t[(2*lbs)*j+2*i+1]*t[(2*lbs)*j+2*i+1]+t[(2*lbs)*j+2*i+2]+t[(2*lbs)*j+2*i+2]);
			if(max<t[(2*lbs)*j+2*i+1])
				max=t[(2*lbs)*j+2*i+1];
		}
	for(j=0;j<height;j++)
		for(i=0;i<lbs;i++)
		{
			p=p_data+lbs*j+i;
			*(p)=t[(2*lbs)*j+2*i+1]*255.0/max;
		}
delete[]t;
delete[]h;
}
