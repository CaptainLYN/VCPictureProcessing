#include"stdafx.h"
#include"JHBHDib.h"
#include"CDib.h"
#include<WindowsX.h>
#define _USE_MATH_DEFINES
#include<cmath>
JHBHDib::JHBHDib()
{}
JHBHDib::~JHBHDib()
{}
void JHBHDib::GetDib(CDib *cdib)
{
	dib=cdib;
}
void JHBHDib::PingYi(int m_Xmove,int m_Ymove)//图像平移
{
	LPBYTE lpSrc;//指向原图像像素的指针
	LPBYTE p_data;//指向原图像数据

	LPBYTE lpDst;//指向要像素的指针
	LPBYTE temp;//指向复制图像数据的指针
	LONG i;//循环变量
	LONG wide,height;//图像的高和宽
	LONG lLineBytes;//图像每行的字节数
	p_data=dib->GetData();
	wide=dib->GetWidth();
	height=dib->GetHeight();
	lLineBytes=((wide*8)+31)/32*4;//计算图像每行的字节数：!!!!4字节对齐，不足补零
	temp=new BYTE[lLineBytes*height];//暂时分配内存，以保存新图像
	lpDst=(LPBYTE)temp;
	memset(lpDst,(BYTE)0,lLineBytes*height);//初始化新分配的内存，初始值为255
	for(i=0;i<wide;i++)//一竖列一竖列的复制
	{
		for(int j=0;j<height;j++)
		{
			lpSrc=(LPBYTE)p_data+lLineBytes*(height-1-j)+i;//计算该像素在原dib中的坐标
			int i0,j0;
			i0=i+m_Xmove;//计算该像素在新dib中的坐标
			j0=j+m_Ymove;
			if(i0>=0&&i0<wide&&j0>=0&&j0<height)//判断是否在新图范围内
			{
				lpDst=(LPBYTE)temp+lLineBytes*(height-1-j0)+i0;
				*lpDst=*lpSrc;//复制像素
			}
			else
			{
				//lpDst=(LPBYTE)temp+lLineBytes*(height-1+j)+i;
				//下面这个完全多余
				//*((unsigned char*)lpDst)=255;//对于原图中没有的像素直接赋值为255
			}
		}
	}
	memcpy(p_data,temp,lLineBytes*height);//赋值平移后的图像：将temp指向的数据复制到p_data
	delete []temp;//释放内存
}
void JHBHDib::JingXiang(bool fangshi)//镜像变换，true是水平镜像，false是垂直镜像
{
	LPBYTE lpSrc;
	LPBYTE p_data;
	LPBYTE lpDst;
	LPBYTE temp;
	LONG i,j;
	long height=dib->GetHeight();
	long width=dib->GetWidth();
	p_data=dib->GetData();
	temp=new BYTE[width*height];
	if(fangshi)
	{
		for(j=0;j<height;j++)
		{
			for(i=0;i<width;i++)
			{
				lpSrc=(LPBYTE)p_data+width*j+i;
				lpDst=(LPBYTE)temp+width*(j+1)-i-1;//一定要减一
				*lpDst=*lpSrc;
			}
		}
	}
	else{
		for(i=0;i<width;i++)
			for(j=0;j<height;j++)
			{
				lpSrc=(LPBYTE)p_data+j*width+i;
				lpDst=(LPBYTE)temp+width*(height-j-1)+i;
				*lpDst=*lpSrc;
			}
	}
	memcpy(p_data,temp,width*height);
	delete []temp;
}

LPBYTE JHBHDib::FangDa(LPBYTE temp,int xzoom,int yzoom,long width,long height,int newwidth,int newheight)//图像的放大，这里改了xzoom和yzoom，因为程序下面要用的也是int，不如直接给int
{
	LPBYTE p_data;//指向原图像
	p_data=dib->GetData();
	LPBYTE lpSrc;//指向原像素
	LPBYTE lpDst;
	long i,j,i0,j0;//,height,width;
	int srclinebyte=((width*8+31)/32)*4;
	int dstlinebyte=((newwidth*8+31)/32)*4;
	for(j=0;j<height;j++)
		for(i=0;i<width;i++)
		{
			lpSrc=(LPBYTE)p_data+srclinebyte*j+i;
			for(j0=0;j0<yzoom;j0++)
				for(i0=0;i0<xzoom;i0++)
				{
					lpDst=(LPBYTE)temp+dstlinebyte*(j*yzoom+j0)+i*xzoom+i0;
					//                          行数           新点坐标
					*lpDst=*lpSrc;
				}
		}
		return temp;
}

void JHBHDib::SuoXiao(float xzoom,float yzoom)
{
	long width,height,newwidth,newheight,i,j,i0,j0;
	LPBYTE p_data,temp,lpSrc,lpDst;
	
	temp=dib->GetData();
	p_data=temp;
	width=dib->GetWidth();
	height=dib->GetHeight();
	newwidth=(long)(width*xzoom+0.5);
	newheight=(long)(height*yzoom+0.5);
	int newlinebytes,linebytes;
		
	if(dib->GetInfo()->bmiHeader.biBitCount==8)//现在就针对灰度图进行运算
	{
		linebytes=((width*8+31)/32)*4;
		newlinebytes=((newwidth*8+31)/32)*4;
	    temp=new BYTE[newlinebytes*newheight];
		for(j=0;j<newheight;j++)
			for(i=0;i<newwidth;i++)
			{
				lpDst=(LPBYTE)temp+newlinebytes*j+i;
				//计算该点在原图中的位置
				j0=(LONG)(j/yzoom+0.5);
				i0=(LONG)(i/xzoom+0.5);
				if((i0>=0&&i0<width)&&(j0>=0&&j0<height))//虽然这里加了判断，但是感觉理论上是不可能不在原图的
				{
					lpSrc=(LPBYTE)p_data+j0*linebytes+i0;
					*lpDst=*lpSrc;
				}
				else
				{
					*lpDst=255;
				}
			}
			
			for(j=0;j<height;j++)
				for(i=0;i<width;i++)
				{
					if(j<newheight&&i<newwidth)
					{
					lpDst=(LPBYTE)temp+newlinebytes*j+i;
					*p_data=*lpDst;
					}
					else *p_data=0;
					p_data++;
				}
				delete[]temp;
		//这里的处理方式和放大是不一样的
				
	}
}
LPBYTE JHBHDib::ZhuanZhi()
{
	long width=dib->GetWidth();
	long height=dib->GetHeight();
	int linebytes=((width*8+31)/32)*4;
	int newlinebytes=(height*8+31)/32*4;
	int i,j;
	LPBYTE lpSrc,lpDst,temp,p_data;
	temp=new BYTE[newlinebytes*width];
	memset(temp,(BYTE)0,newlinebytes*width);
	p_data=dib->GetData();
	for(j=0;j<height;j++)
		for(i=0;i<width;i++)
		{
			lpSrc=(LPBYTE)p_data+linebytes*j+i;
			lpDst=(LPBYTE)temp+newlinebytes*i+j;
			*lpDst=*lpSrc;
		}
		//不用下面这些书因为，图像转置后由于有四字节对齐，所以大小可能会变大，所以，dib类里面销毁的时候大小不对，会出现错误
		dib->GetInfo()->bmiHeader.biHeight=width;
		dib->GetInfo()->bmiHeader.biWidth=height;
		dib->GetInfo()->bmiHeader.biSizeImage=newlinebytes*width;
		//memcpy(p_data,temp,height*width);//这里这样写linebytes*newlinebytes,否则4字节对齐数据不全会出现边缘彩色
		//delete(temp);
		return temp;
}
double JHBHDib::RADIAN(double RotateAngle)
{
	return RotateAngle*M_PI/180;//要有最上面那个define才行
}

LPBYTE JHBHDib::XuanZhuan(double RotateAngle)//原理看懂了，以后不懂的话看pdf版的就可以了
{
	DWORD DstBufSize;
	LPBYTE lpTempPtr,lpPtr,lpSrc,lpTemp;
	double SrcX1,SrcY1,SrcX2,SrcY2,SrcX3,SrcY3,SrcX4,SrcY4;
	double DstX1,DstY1,DstX2,DstY2,DstX3,DstY3,DstX4,DstY4;
	DWORD Wold,Hold,Wnew,Hnew;
	DWORD x0,y0,x1,y1;
	double cosa,sina;//cos(a),sin(a)
	double num1,num2;
	
	//角度到弧度的变化
	RotateAngle=(double)RADIAN(RotateAngle);
	cosa=(double)cos((double)RotateAngle);
	sina=(double)sin((double)RotateAngle);

	//CString s;
	//s.Format(_T("%lf"),RotateAngle);//将RotateAngle转化为字符串
	//MessageBox(NULL,s,_T("提示"),MB_OK);//用来测试对不对

	lpSrc=dib->GetData();
	Wold=dib->GetWidth();
	Hold=dib->GetHeight();
	//原图的4个角的坐标
	SrcX1=(double)(-0.5*Wold);
	SrcY1=(double)(0.5*Hold);
	SrcX2=(double)(0.5*Wold);
	SrcY2=(double)(0.5*Hold);
	SrcX3=(double)(-0.5*Wold);
	SrcY3=(double)(-0.5*Hold);
	SrcX4=(double)(0.5*Wold);
	SrcY4=(double)(-0.5*Hold);
	//新图的四个角坐标
	DstX1=cosa*SrcX1+sina*SrcY1;
	DstY1=-sina*SrcX1+cosa*SrcY1;
	DstX2=cosa*SrcX2+sina*SrcY2;
	DstY2=-sina*SrcX2+cosa*SrcY2;
	DstX3=cosa*SrcX3+sina*SrcY3;
	DstY3=-sina*SrcX3+cosa*SrcY3;
	DstX4=cosa*SrcX4+sina*SrcY4;
	DstY4=-sina*SrcX4+cosa*SrcY4;
	//新图的宽度和高度
	Wnew=(DWORD)(max(fabs(DstX4-DstX1),fabs(DstX3-DstX2))+0.5);
	Hnew=(DWORD)(max(fabs(DstY4-DstY1),fabs(DstY3-DstY2))+0.5);
	//计算矩阵中的两个常数，这样不用每次都算
	num1=(double)(-0.5*Wnew*cosa-0.5*Hnew*sina+0.5*Wold);
	num2=(double)(0.5*Wnew*sina-0.5*Hnew*cosa+0.5*Hold);
	
	//这里我选择linebytes，书上不是
	int newlinebytes=((Wnew*8+31)/32)*4;
	int linebytes=((Wold*8+31)/32)*4;

	DstBufSize=newlinebytes*Hnew;
	//DstBufSize=Wnew*Hnew;
	//原书填入的是白色，虽然我认为要填黑色，但是为了显示效果，还是先暂且选择白色
	//关于缓冲区，有时候书上是linebytes，有时候又是简单的高和宽的乘积？？
	lpTempPtr=new BYTE[DstBufSize];
	memset(lpTempPtr,(BYTE)255,DstBufSize);
	lpTemp=lpTempPtr;//保存住总入口
	for(y1=0;y1<Hnew;y1++)
	{
		for(x1=0;x1<Wnew;x1++)
		{
			//x0,y0是该点在原图上的坐标
			x0=(DWORD)(x1*cosa+y1*sina+num1);
			y0=(DWORD)(-1.0f*x1*sina+y1*cosa+num2);
			if(x0>=0&&x0<Wold&&y0>=0&&y0<Hold)//在原图范围内
			{
				lpPtr=lpSrc+y0*linebytes+x0;
				//lpPtr=lpSrc+y0*Wold+x0;//像原书这样是不对的
				lpTempPtr=lpTemp+y1*newlinebytes+x1;
				//lpTempPtr=lpTemp+y1*Wnew+x1;
				*lpTempPtr=*lpPtr;
				
				//lpTempPtr=lpTemp;

			}
		}
	}
	dib->GetInfo()->bmiHeader.biHeight=Hnew;
	dib->GetInfo()->bmiHeader.biWidth=Wnew;
	dib->GetInfo()->bmiHeader.biSizeImage=newlinebytes*Hnew;

	return lpTemp;
}