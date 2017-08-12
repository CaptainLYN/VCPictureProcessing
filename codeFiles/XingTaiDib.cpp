#include "StdAfx.h"
#include "XingTaiDib.h"
#include"CDib.h"
#include<WindowsX.h>
#include"FenGeCeLiangDib.h"

XingTaiDib::XingTaiDib(void)
{
}

XingTaiDib::~XingTaiDib(void)
{
}
void XingTaiDib::GetDib(CDib *d)
{
	dib=d;
}
void XingTaiDib::ShuiPingFuShi()
{
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	int lbs=dib->GetDibWidthBytes();
	LPBYTE p_data=dib->GetData();
	LPBYTE temp=new BYTE[lbs*height];//用于保存新图像
	LPBYTE lpSrc,lpDst;
	memset(temp,255,sizeof(BYTE)*lbs*height);
	
	for(int j=0;j<height;j++)
		for(int i=1;i<width-1;i++)
		{
			lpSrc=p_data+lbs*j+i;
			lpDst=temp+lbs*j+i;
			*lpDst=0;//先将这个点赋值为heise
			for(int n=0;n<3;n++)
				if(*(lpSrc+(n-1))==255)
				{
					*lpDst=255;
					break;
				}

		}
		memcpy(p_data,temp,sizeof(BYTE)*lbs*height);
		delete[]temp;
}
void XingTaiDib::ChuiZhiFuShi()
{
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	int lbs=dib->GetDibWidthBytes();
	LPBYTE p_data=dib->GetData();
	LPBYTE temp=new BYTE[lbs*height];//用于保存新图像
	LPBYTE lpSrc,lpDst;
	memset(temp,255,sizeof(BYTE)*lbs*height);
	
	for(int j=1;j<height-1;j++)
		for(int i=0;i<width;i++)
		{
			lpSrc=p_data+lbs*j+i;
			lpDst=temp+lbs*j+i;
			*lpDst=0;//先将这个点赋值为heise
			for(int n=0;n<3;n++)
				if(*(p_data+(n-1+j)*lbs+i)==255)
				{
					*lpDst=255;
					break;
				}

		}
		memcpy(p_data,temp,sizeof(BYTE)*lbs*height);
		delete[]temp;
}
void XingTaiDib::QuanFangXiangFuShi()
{
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	int lbs=dib->GetDibWidthBytes();
	LPBYTE p_data=dib->GetData();
	LPBYTE temp=new BYTE[lbs*height];
	memset(temp,255,sizeof(BYTE)*lbs*height);
	LPBYTE lpSrc,lpDst;
	int b[9]={1,0,1,0,0,0,1,0,1};//结构元素数组
	for(int j=1;j<height-1;j++)
		for(int i=1;i<width;i++)
		{
			lpSrc=p_data+lbs*j+i;
			lpDst=temp+lbs*j+i;
			*lpDst=0;//先赋值为黑色
			for(int m=0;m<3;m++)
				for(int n=0;n<3;n++)
				{
					if(b[m+n]==1)
						continue;
					if(*(p_data+(m-1+j)*lbs+n-1+i)==255)
						{
							*lpDst=255;
							break;
						}
				}
		}
		memcpy(p_data,temp,sizeof(BYTE)*lbs*height);
		delete[]temp;
}
void XingTaiDib::ShuiPingPengZhang()
{
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	int lbs=dib->GetDibWidthBytes();
	LPBYTE p_data=dib->GetData();
	LPBYTE temp=new BYTE[lbs*height];//用于保存新图像
	LPBYTE lpSrc,lpDst;
	memset(temp,255,sizeof(BYTE)*lbs*height);

	for(int j=0;j<height;j++)
		for(int i=1;i<width-1;i++)
		{
			lpSrc=p_data+lbs*j+i;
			lpDst=temp+lbs*j+i;
			//*lpDst=255;//先将这个点赋值为heise
			for(int n=0;n<3;n++)
				if(*(lpSrc+(n-1))==0)
				{
					*lpDst=0;
					break;
				}

		}
		memcpy(p_data,temp,sizeof(BYTE)*lbs*height);
		delete[]temp;
}
void XingTaiDib::ChuiZhiPengZhang()
{
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	int lbs=dib->GetDibWidthBytes();
	LPBYTE p_data=dib->GetData();
	LPBYTE temp=new BYTE[lbs*height];//用于保存新图像
	LPBYTE lpSrc,lpDst;
	memset(temp,255,sizeof(BYTE)*lbs*height);
	
	for(int j=1;j<height-1;j++)
		for(int i=0;i<width;i++)
		{
			lpSrc=p_data+lbs*j+i;
			lpDst=temp+lbs*j+i;
			//*lpDst=0;//先将这个点赋值为heise
			for(int n=0;n<3;n++)
				if(*(p_data+(n-1+j)*lbs+i)==0)
				{
					*lpDst=0;
					break;
				}

		}
		memcpy(p_data,temp,sizeof(BYTE)*lbs*height);
		delete[]temp;
}
void XingTaiDib::QuanFangXiangPengZhang()
{
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	int lbs=dib->GetDibWidthBytes();
	LPBYTE p_data=dib->GetData();
	LPBYTE temp=new BYTE[lbs*height];
	memset(temp,255,sizeof(BYTE)*lbs*height);
	LPBYTE lpSrc,lpDst;
	int b[9]={1,0,1,0,0,0,1,0,1};//结构元素数组
	for(int j=1;j<height-1;j++)
		for(int i=1;i<width;i++)
		{
			lpSrc=p_data+lbs*j+i;
			lpDst=temp+lbs*j+i;
			//*lpDst=0;//先赋值为黑色
			for(int m=0;m<3;m++)
				for(int n=0;n<3;n++)
				{
					if(b[m+n]==1)
						continue;
					if(*(p_data+(m-1+j)*lbs+n-1+i)==0)
						{
							*lpDst=0;
							break;
						}
				}
		}
		memcpy(p_data,temp,sizeof(BYTE)*lbs*height);
		delete[]temp;
}
void XingTaiDib::BiYuanSuan()
{
	QuanFangXiangPengZhang();
	QuanFangXiangFuShi();
}
void XingTaiDib::KaiYunSuan()
{
	QuanFangXiangFuShi();
	QuanFangXiangPengZhang();
}
void XingTaiDib::XiHua()//效果和书上不太一样
{
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	int lbs=dib->GetDibWidthBytes();
	LPBYTE p_data=dib->GetData();
	LPBYTE temp=new BYTE[lbs*height];
	//memset(temp,255,sizeof(BYTE)*lbs*height);
	LPBYTE lpSrc,lpDst;
	bool fp=true;//循环跳出标志
	int i,j,m,n;
	unsigned char s[5][5],num;
	while(fp)
	{
		fp=false;
		memset(temp,255,sizeof(BYTE)*lbs*height);
		for(j=2;j<height-2;j++)
			for(i=2;i<width-2;i++)
			{
				lpSrc=p_data+lbs*j+i;//这里的lbs不小心写了width就会出错，垃圾书籍毁我青春
				lpDst=temp+lbs*j+i;
				if(*lpSrc==255)//如果为白色就跳过
					continue;
				for(m=0;m<5;m++)
					for(n=0;n<5;n++)
					{
						if(*(lpSrc+(m-2)*lbs+n-2)==255)//这里修改了
							s[m][n]=0;
						else 
							s[m][n]=1;
					}
				//判断条件1是否成立
				num=s[1][1]+s[1][2]+s[1][3]+s[2][1]+s[2][3]+s[3][1]+s[3][2]+s[3][3];
				if(num<2||num>6)//条件一不满足就不会同时满足4个条件，保留该点
				{
					*lpDst=0;
					continue;
				}
				//判断条件2是否成立
				num=0;
				if(s[1][2]==0&&s[1][1]==1)
					num++;
				if(s[1][1]==0&&s[2][1]==1)
					num++;
				if(s[2][1]==0&&s[3][1]==1)
					num++;
				if(s[3][1]==0&&s[3][2]==1)
					num++;
				if(s[3][2]==0&&s[3][3]==1)
					num++;
				if(s[3][3]==0&&s[2][3]==1)
					num++;
				if(s[2][3]==0&&s[1][3]==1)
					num++;
				if(s[1][3]==0&&s[1][2]==1)
					num++;
				if(num!=1)
				{
					*lpDst=0;
					continue;//条件2不成立
				}
				//判断条件3是否成立
				if(s[1][2]*s[2][1]*s[2][3]!=0)
				{
					num=0;
					if(s[0][2]==0&&s[0][1]==1)
						num++;
					if(s[0][1]==0&&s[1][1]==1)
						num++;
					if(s[1][1]==0&&s[2][1]==1)
						num++;
					if(s[2][1]==0&&s[2][2]==1)
						num++;
					if(s[2][2]==0&&s[2][3]==1)
						num++;
					if(s[2][3]==0&&s[1][3]==1)
						num++;
					if(s[1][3]==0&&s[0][3]==1)
						num++;
					if(s[0][3]==0&&s[0][2]==1)
						num++;
					if(num==1)
					{
						*lpDst=0;
						continue;
					}
				}
				/*else
				{
					*lpDst=0;
					continue;
				}*/
				//判断条件4是否成立
				if(s[1][2]*s[2][1]*s[3][2]/*=*/!=0)
				{
					num=0;
					if(s[1][1]==0&&s[1][0]==1)
						num++;
					if(s[1][0]==0&&s[2][0]==1)
						num++;
					if(s[2][0]==0&&s[3][0]==1)
						num++;
					if(s[3][0]==0&&s[3][1]==1)
						num++;
					if(s[3][1]==0&&s[3][2]==1)
						num++;
					if(s[3][2]==0&&s[2][2]==1)
						num++;
					if(s[2][2]==0&&s[1][2]==1)
						num++;
					if(s[1][2]==0&&s[1][1]==1)
						num++;
					if(num==1)
					{
						*lpDst=0;
						continue;
					}
				}
				/*else
				{
					*lpDst=0;
						continue;
				}*/
				//如果条件均满足就删除改点
				//*lpDst=255;
				fp=true;
			}
			//复制细化后的图片，一次次重复，直至没有点可以删除为止
			memcpy(p_data,temp,sizeof(BYTE)*lbs*height);
	}
	/*memcpy(p_data,temp,sizeof(BYTE)*lbs*height);*/
	delete[]temp;
}
void XingTaiDib::CuHua()
{
	int height=dib->GetHeight();
	int width=dib->GetWidth();
	int lbs=dib->GetDibWidthBytes();
	LPBYTE p_data=dib->GetData();
	for(int j=0;j<height;j++)
		for(int i=0;i<width;i++)
		{
			if(*(p_data+lbs*j+i)==0)
				*(p_data+lbs*j+i)=255;
			else
				*(p_data+lbs*j+i)=0;
		}
	XiHua();
}
void XingTaiDib::ZhongZhou()//效果和书上的不一样；两个合在一起会一直循环出不来
{
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	int lbs=dib->GetDibWidthBytes();
	LPBYTE p_data=dib->GetData();
	LPBYTE temp=new BYTE[lbs*height];
	//memset(temp,255,sizeof(BYTE)*lbs*height);
	LPBYTE lpSrc,lpDst;
	bool fp=true;//循环跳出标志
	int i,j,m,n;
	unsigned char s[5][5],num;
	while(fp)
	{
		fp=false;
		memset(temp,255,sizeof(BYTE)*lbs*height);
		for(j=2;j<height-2;j++)
			for(i=2;i<width-2;i++)
			{
				lpSrc=p_data+lbs*j+i;//这里的lbs不小心写了width就会出错，垃圾书籍毁我青春
				lpDst=temp+lbs*j+i;
				if(*lpSrc==255)//如果为白色就跳过
					continue;
				for(m=0;m<5;m++)
					for(n=0;n<5;n++)
					{
						if(*(lpSrc+(m-2)*lbs+n-2)==255)//这里修改了
							s[m][n]=0;
						else 
							s[m][n]=1;
					}
				//判断条件1-1是否成立
				num=s[1][1]+s[1][2]+s[1][3]+s[2][1]+s[2][3]+s[3][1]+s[3][2]+s[3][3];
				if(num<2||num>6)//条件一不满足就不会同时满足4个条件，保留该点
				{
					*lpDst=0;
					continue;
				}
				//判断条件1-2是否成立
				num=0;
				if(s[1][2]==0&&s[1][1]==1)
					num++;
				if(s[1][1]==0&&s[2][1]==1)
					num++;
				if(s[2][1]==0&&s[3][1]==1)
					num++;
				if(s[3][1]==0&&s[3][2]==1)
					num++;
				if(s[3][2]==0&&s[3][3]==1)
					num++;
				if(s[3][3]==0&&s[2][3]==1)
					num++;
				if(s[2][3]==0&&s[1][3]==1)
					num++;
				if(s[1][3]==0&&s[1][2]==1)
					num++;
				if(num!=1)
				{
					*lpDst=0;
					continue;//条件2不成立
				}
				//判断条件1-3是否成立
				if(s[1][2]*s[2][1]*s[3][2]!=0)
				{
						*lpDst=0;
						continue;
				}
				//判断条件1-4是否成立
				if(s[2][1]*s[2][3]*s[3][2]!=0)
				{
						*lpDst=0;
						continue;
				}
				//如果条件均满足就删除改点
				//*lpDst=255;
			}
		memcpy(p_data,temp,sizeof(BYTE)*lbs*height);//不加这个就会一直循环跳不出来！！！！！！！！！！！
			//判断第二个条件
		for(j=2;j<height-2;j++)
			for(i=2;i<width-2;i++)
			{
				lpSrc=p_data+lbs*j+i;//这里的lbs不小心写了width就会出错，垃圾书籍毁我青春
				lpDst=temp+lbs*j+i;
				if(*lpSrc==255)//如果为白色就跳过
					continue;
				for(m=0;m<5;m++)
					for(n=0;n<5;n++)
					{
						if(*(lpSrc+(m-2)*lbs+n-2)==255)//这里修改了
							s[m][n]=0;
						else 
							s[m][n]=1;
					}
				//判断条件2-1是否成立
				num=s[1][1]+s[1][2]+s[1][3]+s[2][1]+s[2][3]+s[3][1]+s[3][2]+s[3][3];
				if(num<2||num>6)//条件一不满足就不会同时满足4个条件，保留该点
				{
					*lpDst=0;
					continue;
				}
				//判断条件2-2是否成立
				num=0;
				if(s[1][2]==0&&s[1][1]==1)
					num++;
				if(s[1][1]==0&&s[2][1]==1)
					num++;
				if(s[2][1]==0&&s[3][1]==1)
					num++;
				if(s[3][1]==0&&s[3][2]==1)
					num++;
				if(s[3][2]==0&&s[3][3]==1)
					num++;
				if(s[3][3]==0&&s[2][3]==1)
					num++;
				if(s[2][3]==0&&s[1][3]==1)
					num++;
				if(s[1][3]==0&&s[1][2]==1)
					num++;
				if(num!=1)
				{
					*lpDst=0;
					continue;//条件2不成立
				}
			   //判断2-3是否成立
				if(s[1][2]*s[2][1]*s[2][3]!=0)
				{
					*lpDst=0;
					continue;
				}
				//判断2-4是否成立
				if(s[1][2]*s[2][3]*s[3][2]!=0)
				{
					*lpDst=0;
					continue;
				}
				//如果条件满足就都删掉
				//*lpDst=255;
				fp=true;
			}
			//复制细化后的图片，一次次重复，直至没有点可以删除为止
			memcpy(p_data,temp,sizeof(BYTE)*lbs*height);
	}
	/*memcpy(p_data,temp,sizeof(BYTE)*lbs*height);*/
	delete[]temp;
}