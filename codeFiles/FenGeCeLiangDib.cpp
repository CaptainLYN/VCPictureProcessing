#include"stdafx.h"
#include"CDib.h"
#include<WindowsX.h>
#include"FenGeCeLiangDib.h"
#include"HuiDuDib.h"
#include"HuiDuDib.h"
#include<string>
#include"CViewImage.h"
void FenGeCeLiangDib::GetDib(CDib *d)
{
	dib=d;
}
void FenGeCeLiangDib::YuZhiFenGe(int yuzhi)
{
	int height=dib->GetHeight();
	int width=dib->GetWidth();
	int lbs=dib->GetDibWidthBytes();
	LPBYTE p_data=dib->GetData();
	for(int j=0;j<height;j++)
		for(int i=0;i<width;i++)
		{
			if(p_data[lbs*j+i]>=yuzhi/*abs(p_data[lbs*j+i]-yuzhi)>30*/)
				p_data[lbs*j+i]=255;//原书赋值是错误的，这里修改了
			else
				p_data[lbs*j+i]=0;
		}
}
void FenGeCeLiangDib::BanYuZhi(int yuzhi)
{
	int height=dib->GetHeight();
	int width=dib->GetWidth();
	int lbs=dib->GetDibWidthBytes();
	LPBYTE p_data=dib->GetData();
	for(int j=0;j<height;j++)
		for(int i=0;i<width;i++)
		{
			if(p_data[lbs*j+i]<yuzhi)
				p_data[lbs*j+i]=255;//原书赋值是错误的，这里修改了
		}
}
void FenGeCeLiangDib::DieDaiYuZhi()
{
	HuiDuDib hui;
	hui.GetDib(dib);
	int j1=hui.PingJunHuiDu();
	float *data=hui.ZhiFangTu(true);
	float t0,t1,t2,t3,j2;
	t0=t1=t2=t3=0;
	while(true)
	{
		for(int i=0;i<j1+1;i++)
		{
			t0+=data[i]*i;//总的数量乘以灰度
			t1+=data[i];//总的数量
		}
		for(int i=j1+1;i<256;i++)
		{
			t2+=data[i]*i;
			t3+=data[i];
		}
		j2=(t0/t1+t2/t3)/2;
		if(j2==j1)
			break;//如果均值不再发生变化
		else
			j1=j2;
	}
	//找出各像素均值就进行变换
	YuZhiFenGe(j1);
	delete[]data;
}
void FenGeCeLiangDib::LunKuoTiQu()
{
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	int lbs=dib->GetDibWidthBytes();
	int a[8];
	LPBYTE p_data=dib->GetData();
	LPBYTE temp=new BYTE[lbs*height];
	DieDaiYuZhi();
	memset(temp,255,sizeof(byte)*lbs*height);
	for(int j=1;j<height-1;j++)
		for(int i=1;i<width-1;i++)
		{
			if(p_data[lbs*j+i]==0)
			{
				a[0]=p_data[lbs*(j-1)+i-1];
				a[1]=p_data[lbs*(j-1)+i];
				a[2]=p_data[lbs*(j-1)+i+1];
				a[3]=p_data[lbs*j+i-1];
				a[4]=p_data[lbs*j+i+1];
				a[5]=p_data[lbs*(j+1)+i-1];
				a[6]=p_data[lbs*(j+1)+i];
				a[7]=p_data[lbs*(j+1)+i+1];
				if(a[0]+a[1]+a[2]+a[3]+a[4]+a[5]+a[6]+a[7]==0)
					temp[lbs*j+i]=255;
				else
					temp[lbs*j+i]=0;
			}
		}
		memcpy(p_data,temp,lbs*height);
		delete[]temp;
}
bool FenGeCeLiangDib::BiHeGenZong()
{
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	int lbs=dib->GetDibWidthBytes();
	int i,j;
	bool fs;//是否找到初始点
	bool fp;//是否找到下一个黑点
	int cishu=0;
	CPoint sp,cp;//初始点和当前点坐标
	LPBYTE p_data=dib->GetData();
	LPBYTE temp=new BYTE[lbs*height];
	memset(temp,255,sizeof(byte)*lbs*height);
	int go[8][2]={{-1,-1},{0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1},{-1,0}};//从左上角开始的顺时针8个方向
	int sd;//记录在go数组中的方向
	//先来个二值化
	DieDaiYuZhi();
	fs=false;
	for(j=0;j<height&&!fs;j++)
		for(i=0;i<width&&!fs;i++)
		{
			if(p_data[lbs*j+i]==0)
			{
				fs=true;//找到了初始黑点
				sp.y=j;
				sp.x=i;//记录初始点的位置
				temp[lbs*j+i]=0;
			}
		}
		//由于初始点是左下方，所以扫描沿左上方向
		sd=0;//跟踪边界
		fs=false;
		//从初始点开始扫描
		cp.y=sp.y;
		cp.x=sp.x;
		LPBYTE lpSrc,lpDst;
		while(!fs&&cishu<0x7fffffff)
		{
			cishu++;
			fp=false;
			while(!fp)
			{
				//沿扫描方向查看一个像素
				lpSrc=p_data+lbs*(cp.y+go[sd][1])+cp.x+go[sd][0];
				if(*(lpSrc)==0)
				{
					fp=true;//找到了下一个黑点
					cp.y=cp.y+go[sd][1];
					cp.x=cp.x+go[sd][0];
					if(cp.y==sp.y&&cp.x==sp.x)
						fs=true;//找到了初始点
					lpDst=temp+lbs*cp.y+cp.x;
					*(lpDst)=0;//写上黑点
					//找到了就下一次方向逆时针旋转两格
					sd--;
					if(sd==-1)
						sd=7;
					sd--;
					if(sd==-1)
						sd=7;
				}
				else//如果这一次的方向没有，就顺时针旋转一格
				{
					sd++;
					if(sd==8)
						sd=0;
				}
			}
		}
		if(cishu==0x7fffffff)
		{
			MessageBox(NULL,_T("循环了0x7fffffff次没有结果，判断图中没有闭合圆"),_T("提示"),MB_OK);
			return false;
		}
		else {
		memcpy(p_data,temp,lbs*height);
		delete[]temp;
		return true;
		}
}
void FenGeCeLiangDib::QuYuZengZhang(CPoint pt)
{
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	int lbs=dib->GetDibWidthBytes();
	int i,j,t;
	LPBYTE p_data=dib->GetData();
	int zhongzi=p_data[pt.y*lbs+pt.x];
	for(j=0;j<height;j++)
		for(i=0;i<width;i++)
		{
			t=p_data[j*lbs+i];
			if(abs(t-zhongzi)>10)//标准差设为10
			{
				p_data[lbs*j+i]=255;//不是一个区域，消除，赋成白色
			}
		}
}
int FenGeCeLiangDib::ErZhiBiaoJi(LPBYTE temp,int flag[])
{
	//先来个二值化
	DieDaiYuZhi();
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	LPBYTE p_data=dib->GetData();
	int lbs=dib->GetDibWidthBytes();
	/*temp=new BYTE[lbs*height];*///记录每个点的标记
	/*memset(temp,0,sizeof(BYTE)*lbs*height);*/
	BYTE x_temp,y_temp;
	int x_sign=0;
	//memset(flag,0,255*sizeof(int));//每个标记的数量，0不用，现在默认不超过255个图像
	for(int j=1;j<height-1;j++)
		for(int i=1;i<width-1;i++)
		{
			if(p_data[j*lbs+i]==0)//如果当前点是黑点的话
			{
				if(p_data[(j-1)*lbs+i+1]==0)//如果右上点是黑点的话
				{
					temp[j*lbs+i]=temp[(j-1)*lbs+i+1];//将当前区域值设置为跟右上角是一样的
					x_temp=temp[j*lbs+i];
					flag[x_temp]+=1;
					if(p_data[j*lbs+i-1]==0&&temp[j*lbs+i-1]!=x_temp)//如果左前点是黑点，但是标记的值和当前点不一样、
					{
						y_temp=temp[j*lbs+i-1];
						for(int m=1;m<height-1;m++)//这里？？？？？？？？？？
							for(int n=1;n<width-1;n++)
							{
								if(temp[m*lbs+n]==y_temp)
								{
									flag[y_temp]=0;
									flag[x_temp]+=1;
									temp[m*lbs+n]=x_temp;//修改值
								}
							}
					}
					if(p_data[(j-1)*lbs+i-1]==0&&temp[(j-1)*lbs+i-1]!=x_temp)//如果左上点是黑点，但是跟当前记录值不一样
					{
						y_temp=temp[(j-1)*lbs+i-1];
						for(int m=1;m<height;m++)
							for(int n=1;n<width;n++)
							{
								if(temp[m*lbs+n]==y_temp)
								{
									flag[y_temp]=0;
									flag[x_temp]+=1;
									temp[m*lbs+n]=x_temp;//修改值
								}
							}
					}
				}
				else if(p_data[(j-1)*lbs+i]==0)//如果右上方不是0，而正上方是0
				{
					temp[j*lbs+i]=temp[(j-1)*lbs+i];
					y_temp=temp[j*lbs+i];
					flag[y_temp]+=1;
				}
				else if(p_data[(j-1)*lbs+i-1]==0)//如果左上方是0
				{
					temp[j*lbs+i]=temp[(j-1)*lbs+i-1];
					y_temp=temp[j*lbs+i];
					flag[y_temp]+=1;
				}
				else if(p_data[j*lbs+i-1]==0)//如果左前方是0
				{
					temp[j*lbs+i]=temp[j*lbs+i-1];
					y_temp=temp[j*lbs+i];
					flag[y_temp]+=1;
				}
				else
				{
					++x_sign;//标记号加1
					temp[j*lbs+i]=x_sign;
					flag[x_sign]=1;
				}
			}
		}
		//调试了好久终于知道了，x_sign会很大，而分出来的图像块远小于这个是因为，中间有些回溯后数据改了，但是即使那个数都不见了，x_sign还是会继续增长
		/*BYTE t[256*256];
		memcpy(t,temp,256*256);*/
		return x_sign;//将new的数组返回，记得删除内存
}
void  FenGeCeLiangDib::ErZhiZhouChang()
{
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	int lbs=dib->GetDibWidthBytes();
	LPBYTE p_data=dib->GetData();
	int flag[256]={0};
	LPBYTE p_temp=new BYTE[lbs*height];
	memset(p_temp,255,sizeof(BYTE)*lbs*height);
	int x_sign=ErZhiBiaoJi(p_temp,flag);//先用标记法求出物体区域
	LPBYTE lpSrc,lpDst;
	CPoint sp,cp;//起始边界点和当前边界点
	int dc[8][2]={{-1,-1},{0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1},{-1,0}};//8个起始扫描方向，从左下方开始顺时针旋转！！！书上写错了
	int bd;//起始的方向号
	LPBYTE temp=new BYTE[lbs*height];//用于保存新图像
	memset(temp,255,sizeof(BYTE)*lbs*height);//新图像底色是白色，将轮廓填充为黑点
	bool fsp,fp;//找到初始点；找到下一个点
	/*CViewImage ima;
	ima.GetDib(dib);
	ima.OnDraw3(pDC,p_temp,dib->GetWidth(),0);*/
	for(int t=1;t<=x_sign;t++)
	{
		if(flag[t]!=0)//有几个物体就会有几个轮廓
		{
			fsp=false;
			for(int j=0;j<height&&!fsp;j++)//扫描图片，找到第一个黑点
				for(int i=0;i<width&&!fsp;i++)
				{
					lpSrc=p_temp+lbs*j+i;
					if(*lpSrc==t)
					{
						fsp=true;//找到了初始点
						sp.y=j;
						sp.x=i;
						temp[lbs*j+i]=t;//在新图像中把第一个点标上
					}
				}
				bd=0;//起始点在左下方向
				fsp=false;//起始时候还没有找到一个点
				cp.y=sp.y;
				cp.x=sp.x;
				while(!fsp)
				{
					fp=false;
					while(!fp)
					{
						//沿扫描方向查看一个像素
						lpSrc=p_temp+lbs*(cp.y+dc[bd][1])+cp.x+dc[bd][0];
						if(*lpSrc==t)//如果找到了一个和初始点一样的点
						{
							fp=true;
							cp.y=cp.y+dc[bd][1];
							cp.x=cp.x+dc[bd][0];//修改当前点的值为新发现的值
							if(cp.x==sp.x&&cp.y==sp.y)
								fsp=true;//找到了初始点
							lpDst=temp+lbs*cp.y+cp.x;
							*lpDst=t;//在新图中将找到的点标记出来
							//找到了一个点就逆时针旋转90度，左手法则
							bd--;
							if(bd==-1)
								bd=7;
							bd--;
							if(bd==-1)
								bd=7;
						}
						else//如果没有找到
						{
							//扫描顺时针旋转45度
							bd++;
							if(bd==8)
								bd=0;
						}
					}
				}
		}
	}
	
	memcpy(p_data,temp,sizeof(BYTE)*lbs*height);//这里把只有边缘的图像拷给了原图指针
	
	//统计边的长度
	int data;
	int fm[256]={0};//记录周长
	for(int j=0;j<height;j++)
		for(int i=0;i<width;i++)
		{
			data=p_data[lbs*j+i];
			if(data!=0)
			{
				fm[data]+=1;//函数退出时堆栈损坏：数组越界！data的值在0~255，是256个，一开始fm和fn都是255，但是fm[data]中会越界！
			}
		}
	//再来一个数组记录点的总周长
	int fn[256]={0};
	int line=0;
	int zhou=0;//周长
	/*memset(fn,0,256*sizeof(int));*/
	for(int i=1;i<=x_sign;i++)
	{
		if(fm[i]!=0)
		{
			if(fn[line]==0)
			{
				fn[line]=fm[i];
				++line;
			}
			zhou+=fm[i];
		}
	}
	//这里只是输出一个周长，其他的每个物体的周长这里没有显示，以后需要可以调用
	CString s;//CString 是MFC的类
	s.Format(_T("连通区个数：%5d,周长:%10d"),line,zhou);
	MessageBox(NULL,s,_T("周长"),MB_OK);
	delete[] p_temp;
	delete[]temp;
	//花了很长时间解决了方向数组设错的问题，函数退出时的fm堆栈损坏也已经解决！
}
void  FenGeCeLiangDib::XiaoChuXiaoQuYu(int m_value)
{
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	int lbs=dib->GetDibWidthBytes();
	LPBYTE temp=new BYTE[lbs*height];
	memset(temp,255,sizeof(BYTE)*lbs*height);
	int flag[256]={0};
	int x_sign=ErZhiBiaoJi(temp,flag);
	LPBYTE p_data=dib->GetData();
	for(int i=1;i<=x_sign;i++)
	{
		if(flag[i]<m_value)
		{
			for(int m=1;m<height-1;m++)
				for(int n=1;n<width-1;n++)
				{
					if(temp[lbs*m+n]==i)
						temp[lbs*m+n]=255;
				}
		}
	}
	memcpy(p_data,temp,sizeof(BYTE)*lbs*height);
	delete[]temp;
}
void  FenGeCeLiangDib::ShuiPingTouYing()//运行比较慢，不知道为什么，应该是有迭代阈值吧
{
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	LPBYTE p_data=dib->GetData();
	int lbs=dib->GetDibWidthBytes();
	DieDaiYuZhi();//先进行二值化
	int num;
	LPBYTE temp=new BYTE[lbs*height];
	memset(temp,255,sizeof(BYTE)*lbs*height);
	for(int j=0;j<height;j++)
	{
		num=0;
		for(int i=0;i<width;i++)
			if(p_data[lbs*j+i]==0)
				num++;
		for(int i=0;i<num;i++)
			temp[lbs*j+i]=0;
	}
	memcpy(p_data,temp,sizeof(BYTE)*lbs*height);
	delete[]temp;
}
void FenGeCeLiangDib::ChuiZhiTouYing()
{
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	LPBYTE p_data=dib->GetData();
	int lbs=dib->GetDibWidthBytes();
	DieDaiYuZhi();//先进行二值化
	int num;
	LPBYTE temp=new BYTE[lbs*height];
	memset(temp,255,sizeof(BYTE)*lbs*height);
	for(int i=0;i<width;i++)
	{
		num=0;
		for(int j=0;j<height;j++)
			if(p_data[lbs*j+i]==0)
				num++;
		for(int j=0;j<num;j++)
			temp[lbs*j+i]=0;//图像的存储是下面的在上面，所以我们在上面写，显示的时候就是显示在下面，正好是垂直投影
	}
	memcpy(p_data,temp,sizeof(BYTE)*lbs*height);
	delete[]temp;
}