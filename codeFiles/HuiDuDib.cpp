#include"stdafx.h"
#include"CViewImage.h"
#include"CDib.h"
#include<WindowsX.h>
#include"ZhiFangDlg.h"
#include"HuiDuDib.h"

void HuiDuDib::Fei0()//Luna的图片全是白色
{
	LPBYTE p_data=dib->GetData();
	LPBYTE t;
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	int linebytes=dib->GetDibWidthBytes();//其实早已经写好了每行字节的获取方法，一直没用
	for(int j=0;j<height;j++)
		for(int i=0;i<width;i++)
		{
			t=p_data+j*linebytes+i;//书上的写的比较辣鸡
			if(*t>0)
				*t=255;
		}
}
void HuiDuDib::GetDib(CDib *d)
{
	dib=d;
}
void HuiDuDib::GuDing(int YuZhi)
{
	LPBYTE p_data,p;
	p_data=dib->GetData();
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	int linebytes=dib->GetDibWidthBytes();
	for(int j=0;j<height;j++)
		for(int i=0;i<width;i++)
		{
			p=p_data+j*linebytes+i;
			if(*p<YuZhi)
				*p=0;
			else
				*p=255;
		}
}
void HuiDuDib::ShuangYu(int low,int high,int mode)
{
	LPBYTE p_data=dib->GetData();
	LPBYTE t;
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	int linebytes=dib->GetDibWidthBytes();
	switch(mode)
	{
	case 0://0-255-0
	for(int j=0;j<height;j++)
		for(int i=0;i<width;i++)
		{
			t=p_data+j*linebytes+i;
			if(*t<=low||*t>=high)
				*t=0;
			else
				*t=255;
		}
		break;
		case 1://255-0-255
	for(int j=0;j<height;j++)
		for(int i=0;i<width;i++)
		{
			t=p_data+j*linebytes+i;
			if(*t<=low||*t>=high)
				*t=255;
			else
				*t=0;
		}
		break;
	}
	
}
void HuiDuDib::FanSe()
{
	LPBYTE p_data=dib->GetData();
	LPBYTE t;
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	int linebytes=dib->GetDibWidthBytes();
	for(int j=0;j<height;j++)
		for(int i=0;i<width;i++)
		{
			t=p_data+linebytes*j+i;
			*t=255-*t;
		}
}
void HuiDuDib::ChuangKou(BYTE low,BYTE high)
{
	LPBYTE p_data=dib->GetData();
	LPBYTE t;
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	int linebytes=dib->GetDibWidthBytes();
	for(int j=0;j<height;j++)
		for(int i=0;i<width;i++)
		{
			t=p_data+j*linebytes+i;
			if(*t<low)
				*t=0;
			else if(*t>high)
				*t=255;
		}
}
void HuiDuDib::ZheXian(BYTE X1,BYTE Y1,BYTE X2,BYTE Y2)
{
	LPBYTE p_data=dib->GetData();
	LPBYTE t;
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	int linebytes=dib->GetDibWidthBytes();
	for(int j=0;j<height;j++)
		for(int i=0;i<width;i++)
		{
			t=p_data+linebytes*j+i;
			if(*t>0&&*t<=X1)
			{
				*t=*t*(Y1/X1);
			}
			else if(*t<X1&&*t<X2)
			{
				*t=Y1+(Y2-Y1)/(X2-X1)*(*t-X1);
			}
			else if(X2!=255)
			{
				*t=Y2+(255-Y2)/(255-X2)*(*t-X2);
			}
		}
}
float* HuiDuDib::ZhiFangTu(bool moshi)
{
	float *tongji=new float[256];//要记得销毁
	
	memset(tongji,0,sizeof(float)*256);
	BYTE* p_data=dib->GetData();
	BYTE *temp;
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	int linebytes=dib->GetDibWidthBytes();
	int i,j;
	for(j=0;j<height;j++)
	{
		for(i=0;i<width;i++)
		{
			temp=p_data+j*linebytes+i;
			tongji[*temp]++;
		}
	}
	if(moshi==true)
	{
	for(i=0;i<256;i++)
		tongji[i]=tongji[i]/(height*width);
	}
	return tongji;
}
void HuiDuDib::FenBuJunHengHua()
{
	int i,j;
	//灰度分布密度
	float *fPs_R;
	//中间变量
	float temp_r[256];//就是S[]累计函数
	int nNs_R[256];//就是L[]，r对应的新像素值
	//初始化
	memset(temp_r,0,sizeof(temp_r));
	LPBYTE p_data=dib->GetData();
	fPs_R=ZhiFangTu(true);//这里是跟书处理不一样的
	//进行均衡化处理
	for(i=0;i<256;i++)
	{
		if(i==0)
			temp_r[0]=fPs_R[0];
		else
			temp_r[i]=temp_r[i-1]+fPs_R[i];
		nNs_R[i]=(int)(255.0f*temp_r[i]+0.5f);//+0.5f为了减少精度的缺失，满足四舍五入
	}
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	unsigned char temp;
	int linebytes=dib->GetDibWidthBytes();
	//对各像素进行灰度转换
	for(j=0;j<height;j++)
		for(i=0;i<width;i++)
		{
			temp=*((unsigned char*)p_data+linebytes*j+i);//8位数据
			*((unsigned char*)p_data+linebytes*j+i)=nNs_R[temp];
		}
	delete []fPs_R;
}
void HuiDuDib::PiPeiBianHuan(BYTE jishu,int* huidu,float *shuju)
{
	long i,j;
	int daiti[256];//记录每个像素被代替为哪一个像素
	float *gailv;//灰度分布概率
	float temp[256];
	LPBYTE p_data=dib->GetData();
	long width=dib->GetWidth();
	long height=dib->GetHeight();
	gailv=ZhiFangTu(true);
	//计算原始累计直方图
	for(i=0;i<256;i++)
	{
		if(i==0)
			temp[0]=gailv[0];
		else
			temp[i]=temp[i-1]+gailv[i];
		gailv[i]=temp[i];
	}
	//计算规定的累积直方图
	for(i=0;i<256;i++)
	{
		if(i==0)
			temp[0]=shuju[0];
		else
			temp[i]=temp[i-1]+shuju[i];
		shuju[i]=temp[i];
	}
	for(i=0;i<256;i++)
	{
		//最接近的规定直方图灰度等级，用规定的直方图等级代替概率差不多的等级
		//让原来的直方图的形状大体接近规定的直方图
		int m_r=0;
		//最小差值
		float min_value_r=1;
		for(j=0;j<jishu;j++)
		{
			//当前差值
			float now_value=0;
			//计算差值
			if(gailv[i]-shuju[j]>=0)
				now_value=gailv[i]-shuju[j];
			else
				now_value=shuju[j]-gailv[i];
			//寻找最接近的规定直方图灰度级
			if(now_value<min_value_r)
			{
				m_r=j;
				min_value_r=now_value;
			}
		}
		//建立灰度映射表，即用规定直方图的哪一个值代替当前灰度值
		daiti[i]=huidu[m_r];
	}
	//对各像素进行处理
	int linebytes=dib->GetDibWidthBytes();
	unsigned char t;
	for(j=0;j<height;j++)
	{
		for(i=0;i<width;i++)
		{
			t=*((unsigned char*)p_data+linebytes*j+i);
			*((unsigned char*)p_data+linebytes*j+i)=daiti[t];
		}
	}
}
int HuiDuDib::PingJunHuiDu()
{
	float* data=ZhiFangTu(true);
	float shu=0;
	for(int i=0;i<256;i++)
		shu+=data[i]*i;
	return (int)(shu+0.5);
}