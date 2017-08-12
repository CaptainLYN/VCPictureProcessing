#include"stdafx.h"
#include<WindowsX.h>
#include"CDib.h"
#include"BianYuanDib.h"
#include<cmath>
void BianYuanDib::GetDib(CDib *d)
{
	dib=d;
}
void BianYuanDib::ZongXiang()
{
	int height=dib->GetHeight();
	int width=dib->GetWidth();
	int lbs=dib->GetDibWidthBytes();
	LPBYTE p_data=dib->GetData();
	LPBYTE temp=new BYTE[lbs*height];
	memset(temp,0,sizeof(byte)*lbs*height);
	//图像最右边设置为黑色吧暂时示例
	for(int j=0;j<height;j++)
		for(int i=0;i<width;i++)
		{
			if(i!=0)
				temp[j*lbs+i]=abs(p_data[j*lbs+i]-p_data[j*lbs+i-1]);
			else
				temp[j*lbs+i]=0;//赋予黑色
		}
		memcpy(p_data,temp,lbs*height);
		delete[]temp;
}
void BianYuanDib::HengXiang()
{
	int height=dib->GetHeight();
	int width=dib->GetWidth();
	int lbs=dib->GetDibWidthBytes();
	LPBYTE p_data=dib->GetData();
	LPBYTE temp=new BYTE[lbs*height];
	memset(temp,0,sizeof(byte)*lbs*height);
	//图像最右边设置为黑色吧暂时示例
	for(int j=0;j<height;j++)
		for(int i=0;i<width;i++)
		{
			if(j!=0)
				temp[j*lbs+i]=abs(p_data[j*lbs+i]-p_data[(j-1)*lbs+i]);
			else
				temp[j*lbs+i]=0;//赋予黑色
		}
		memcpy(p_data,temp,lbs*height);
		delete[]temp;
}
void BianYuanDib::ShuangXiang()
{
	int height=dib->GetHeight();
	int width=dib->GetWidth();
	int lbs=dib->GetDibWidthBytes();
	LPBYTE p_data=dib->GetData();
	LPBYTE temp=new BYTE[lbs*height];
	memset(temp,0,sizeof(byte)*lbs*height);
	float h,z;
	//图像最右边设置为黑色吧暂时示例
	for(int j=0;j<height;j++)
		for(int i=0;i<width;i++)
		{
			if(j!=0&&i!=0)
			{
				h=p_data[lbs*j+i]-p_data[lbs*j+i-1];
				z=p_data[lbs*j+i]-p_data[lbs*(j-1)+i];
				temp[j*lbs+i]=(int)sqrt(h*h+z*z);
			}
			else
				temp[j*lbs+i]=0;//赋予黑色
		}
		memcpy(p_data,temp,lbs*height);
		delete[]temp;
}
void BianYuanDib::MenXianRuiHua(byte t)
{
	int height=dib->GetHeight();
	int width=dib->GetWidth();
	int lbs=dib->GetDibWidthBytes();
	LPBYTE p_data=dib->GetData();
	LPBYTE temp=new BYTE[lbs*height];
	memset(temp,0,sizeof(byte)*lbs*height);
	float h,z,p;
	//图像最右边设置为黑色吧暂时示例
	for(int j=0;j<height;j++)
		for(int i=0;i<width;i++)
		{
			if(j!=0&&i!=0)
			{
				h=p_data[lbs*j+i]-p_data[lbs*j+i-1];
				z=p_data[lbs*j+i]-p_data[lbs*(j-1)+i];
				p=(int)sqrt(h*h+z*z);
				if(p>=t)//如果超过门限值
				{
					if((p+100)>255)
						temp[lbs*j+i]=255;
					else
						temp[lbs*j+i]=p+100;
				}
				else
					temp[j*lbs+i]=p_data[j*lbs+i];
			}
			else
				temp[j*lbs+i]=p_data[j*lbs+i];//赋予黑色
		}
		memcpy(p_data,temp,lbs*height);
		delete[]temp;
}
void BianYuanDib::GuDingRuiHua()
{
	int height=dib->GetHeight();
	int width=dib->GetWidth();
	int lbs=dib->GetDibWidthBytes();
	LPBYTE p_data=dib->GetData();
	LPBYTE temp=new BYTE[lbs*height];
	memset(temp,0,sizeof(byte)*lbs*height);
	float h,z,p;
	//图像最右边设置为黑色吧暂时示例
	for(int j=0;j<height;j++)
		for(int i=0;i<width;i++)
		{
			if(j!=0&&i!=0)
			{
				h=p_data[lbs*j+i]-p_data[lbs*j+i-1];
				z=p_data[lbs*j+i]-p_data[lbs*(j-1)+i];
				p=(int)sqrt(h*h+z*z);
				if(p>=30)//如果超过门限值
				{
					temp[lbs*j+i]=255;//固定为255
				}
				else
					temp[j*lbs+i]=p_data[j*lbs+i];
			}
			else
				temp[j*lbs+i]=p_data[j*lbs+i];//赋予黑色
		}
		memcpy(p_data,temp,lbs*height);
		delete[]temp;
}
void BianYuanDib::ErZhiRuiHua()
{
	int height=dib->GetHeight();
	int width=dib->GetWidth();
	int lbs=dib->GetDibWidthBytes();
	LPBYTE p_data=dib->GetData();
	LPBYTE temp=new BYTE[lbs*height];
	memset(temp,0,sizeof(byte)*lbs*height);
	float h,z,p;
	
	for(int j=0;j<height;j++)
		for(int i=0;i<width;i++)
		{
			if(j!=0&&i!=0)
			{
				h=p_data[lbs*j+i]-p_data[lbs*j+i-1];
				z=p_data[lbs*j+i]-p_data[lbs*(j-1)+i];
				p=(int)sqrt(h*h+z*z);
				if(p>=30)//如果超过门限值
				{
					temp[lbs*j+i]=255;//固定为255
				}
				else
					temp[j*lbs+i]=0;
			}
			else
				temp[j*lbs+i]=p_data[j*lbs+i];//赋予黑色
		}
		memcpy(p_data,temp,lbs*height);
		delete[]temp;
}
void BianYuanDib::Robert()
{
	int height=dib->GetHeight();
	int width=dib->GetWidth();
	float pixe[4];
	int lbs=dib->GetDibWidthBytes();
	LPBYTE p_data=dib->GetData();
	LPBYTE temp=new BYTE[lbs*height];
	/*memset(temp,0,sizeof(byte)*lbs*height);*/
	float h,z,p;
	
	for(int j=0;j<height;j++)
		for(int i=0;i<width;i++)
		{
			if(j!=height-1&&i!=width-1)
			{
				pixe[0]=p_data[j*lbs+i];
				pixe[1]=p_data[(j+1)*lbs+i+1];
				pixe[2]=p_data[j*lbs+i+1];
				pixe[3]=p_data[(j+1)*lbs+i];
				temp[lbs*j+i]=sqrt((pixe[0]-pixe[1])*(pixe[0]-pixe[1])+(pixe[2]-pixe[3])*(pixe[2]-pixe[3]));
			}
			else
				temp[j*lbs+i]=p_data[j*lbs+i];
			if(temp[j*lbs+i]>255)
				temp[j*lbs+i]=255;
		}
		memcpy(p_data,temp,lbs*height);
		delete[]temp;
}
LPBYTE BianYuanDib::Templat(int temph,int tempw,int tempx,int tempy,float main,float *fpArray)
{
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	int lbs=dib->GetDibWidthBytes();
	LPBYTE p_data=dib->GetData();
	LPBYTE temp=new BYTE[lbs*height];
	memset(temp,0,sizeof(BYTE)*lbs*height);
	float result;
	for(int j=tempy;j<height-temph+tempy+1-temph/2;j++)//增加了-temph/2
		for(int i=tempx;i<width-tempw+tempx+1-tempw/2;i++)
		{
			result=0;
			for(int k=0;k<temph;k++)
				for(int l=0;l<tempw;l++)
					result+=p_data[(j-tempy+k)*lbs+(i-tempx+l)]*fpArray[k*tempw+l];
			result=abs(result*main);
			if(result>255)
				temp[j*lbs+i]=255;
			else
				temp[j*lbs+i]=result;
		}
		return temp;
}
void BianYuanDib::Sobel()
{
	float suanzi[9]={-1,-2,-1,0,0,0,1,2,1};
	LPBYTE temp1=Templat(3,3,1,1,1,suanzi);
	suanzi[0]=1;
	suanzi[1]=0;
	suanzi[2]=-1;
	suanzi[3]=2;
	suanzi[4]=0;
	suanzi[5]=-2;
	suanzi[6]=1;
	suanzi[7]=0;
	suanzi[8]=-1;
	LPBYTE temp2=Templat(3,3,1,1,1,suanzi);
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	int lbs=dib->GetDibWidthBytes();
	LPBYTE p_data=dib->GetData();
	for(int j=0;j<height;j++)
		for(int i=0;i<width;i++)
		{
			if(temp1[j*lbs+i]<temp2[j*lbs+i])
				temp1[j*lbs+i]=temp2[j*lbs+i];
		}
		memcpy(p_data,temp1,lbs*height);
		delete[]temp1;
		delete[]temp2;
}
void BianYuanDib::Prewitt()
{
	float suanzi[9]={-1,-1,-1,0,0,0,1,1,1};
	LPBYTE temp1=Templat(3,3,1,1,1,suanzi);
	suanzi[0]=1;
	suanzi[1]=0;
	suanzi[2]=-1;
	suanzi[3]=1;
	suanzi[4]=0;
	suanzi[5]=-1;
	suanzi[6]=1;
	suanzi[7]=0;
	suanzi[8]=-1;
	LPBYTE temp2=Templat(3,3,1,1,1,suanzi);
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	int lbs=dib->GetDibWidthBytes();
	LPBYTE p_data=dib->GetData();
	for(int j=0;j<height;j++)
		for(int i=0;i<width;i++)
		{
			if(temp1[j*lbs+i]<temp2[j*lbs+i])
				temp1[j*lbs+i]=temp2[j*lbs+i];
		}
		memcpy(p_data,temp1,lbs*height);
		delete[]temp1;
		delete[]temp2;
}
void BianYuanDib::Krisch()
{
	//算子1和2进行比较
	float pc=0.5;//这模板系数是怎么来的？？？
	float suanzi[9]={5,5,5,-3,0,-3,-3,-3,-3};
	LPBYTE temp1=Templat(3,3,1,1,pc,suanzi);
	
	suanzi[0]=-3;
	suanzi[1]=5;
	suanzi[2]=5;
	suanzi[3]=-3;
	suanzi[4]=0;
	suanzi[5]=5;
	suanzi[6]=-3;
	suanzi[7]=-3;
	suanzi[8]=-3;
	LPBYTE temp2=Templat(3,3,1,1,pc,suanzi);
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	int lbs=dib->GetDibWidthBytes();
	LPBYTE p_data=dib->GetData();
	for(int j=0;j<height;j++)
		for(int i=0;i<width;i++)
		{
			if(temp1[j*lbs+i]<temp2[j*lbs+i])
				temp1[j*lbs+i]=temp2[j*lbs+i];
		}
	delete[]temp2;
	//和算子3进行比较
	suanzi[0]=-3;
	suanzi[1]=-3;
	suanzi[2]=5;
	suanzi[3]=-3;
	suanzi[4]=0;
	suanzi[5]=5;
	suanzi[6]=-3;
	suanzi[7]=-3;
	suanzi[8]=5;
	temp2=Templat(3,3,1,1,pc,suanzi);
	for(int j=0;j<height;j++)
		for(int i=0;i<width;i++)
		{
			if(temp1[j*lbs+i]<temp2[j*lbs+i])
				temp1[j*lbs+i]=temp2[j*lbs+i];
		}
	delete[]temp2;
//和算子4进行比较
	suanzi[0]=-3;
	suanzi[1]=-3;
	suanzi[2]=-3;
	suanzi[3]=-3;
	suanzi[4]=0;
	suanzi[5]=5;
	suanzi[6]=-3;
	suanzi[7]=5;
	suanzi[8]=5;
	temp2=Templat(3,3,1,1,pc,suanzi);
	for(int j=0;j<height;j++)
		for(int i=0;i<width;i++)
		{
			if(temp1[j*lbs+i]<temp2[j*lbs+i])
				temp1[j*lbs+i]=temp2[j*lbs+i];
		}
	delete[]temp2;
//和算子5进行比较
	suanzi[0]=-3;
	suanzi[1]=-3;
	suanzi[2]=-3;
	suanzi[3]=-3;
	suanzi[4]=0;
	suanzi[5]=-3;
	suanzi[6]=5;
	suanzi[7]=5;
	suanzi[8]=5;
	temp2=Templat(3,3,1,1,pc,suanzi);
	for(int j=0;j<height;j++)
		for(int i=0;i<width;i++)
		{
			if(temp1[j*lbs+i]<temp2[j*lbs+i])
				temp1[j*lbs+i]=temp2[j*lbs+i];
		}
	delete[]temp2;
	//和算子6进行比较
	suanzi[0]=-3;
	suanzi[1]=-3;
	suanzi[2]=-3;
	suanzi[3]=5;
	suanzi[4]=0;
	suanzi[5]=-3;
	suanzi[6]=5;
	suanzi[7]=5;
	suanzi[8]=-3;
	temp2=Templat(3,3,1,1,pc,suanzi);
	for(int j=0;j<height;j++)
		for(int i=0;i<width;i++)
		{
			if(temp1[j*lbs+i]<temp2[j*lbs+i])
				temp1[j*lbs+i]=temp2[j*lbs+i];
		}
	delete[]temp2;
	//和算子7进行比较
	suanzi[0]=5;
	suanzi[1]=-3;
	suanzi[2]=-3;
	suanzi[3]=5;
	suanzi[4]=0;
	suanzi[5]=-3;
	suanzi[6]=5;
	suanzi[7]=-3;
	suanzi[8]=-3;
	temp2=Templat(3,3,1,1,pc,suanzi);
	for(int j=0;j<height;j++)
		for(int i=0;i<width;i++)
		{
			if(temp1[j*lbs+i]<temp2[j*lbs+i])
				temp1[j*lbs+i]=temp2[j*lbs+i];
		}
	delete[]temp2;
	//和算子8进行比较
	suanzi[0]=5;
	suanzi[1]=5;
	suanzi[2]=-3;
	suanzi[3]=5;
	suanzi[4]=0;
	suanzi[5]=-3;
	suanzi[6]=-3;
	suanzi[7]=-3;
	suanzi[8]=-3;
	temp2=Templat(3,3,1,1,pc,suanzi);
	for(int j=0;j<height;j++)
		for(int i=0;i<width;i++)
		{
			if(temp1[j*lbs+i]<temp2[j*lbs+i])
				temp1[j*lbs+i]=temp2[j*lbs+i];
		}
	delete[]temp2;
	memcpy(p_data,temp1,lbs*height);
	delete[]temp1;
}
void BianYuanDib::Guasslaplacian()
{
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	int lbs=dib->GetDibWidthBytes();
	LPBYTE p_data=dib->GetData();
	float suanzi[25]={-2,-4,-4,-4,-2,-4,0,8,0,-4,-4,8,24,8,-4,-4,0,8,0,-4,-2,-4,-4,-4,-2};
	LPBYTE temp=Templat(5,5,4,4,0.25,suanzi);
	memcpy(p_data,temp,lbs*height);
	delete[]temp;
}