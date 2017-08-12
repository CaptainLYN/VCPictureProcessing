#include"stdafx.h"
#include"CDib.h"
#include<WindowsX.h>

#include"CViewImage.h"


void CViewImage::GetDib(CDib *dib2)
{
	dib=dib2;
}

CPalette* CViewImage::CreateBitmapPalette(CDib* pBitmap)
{
	struct mPalette//这里加上名字
	{
		WORD Version;
		WORD NumberOfEntries;
		PALETTEENTRY aEntries[256];//PALETTEENTRY指向一个逻辑调色板
	}palette={0x300,256};//version是0x300

	LPRGBQUAD pRGBTable=pBitmap->GetRGB();//LPRGBQUAD是调色板指针，只有前面是LP的都是指针
	UINT numberOfColors=pBitmap->GetNumberOfColors();
	for(UINT x=0;x<numberOfColors;++x)
	{
		palette.aEntries[x].peRed=pRGBTable[x].rgbRed;//这是第二步，对数组元素和成员变量进行设置
		palette.aEntries[x].peGreen=pRGBTable[x].rgbGreen;
		palette.aEntries[x].peBlue=pRGBTable[x].rgbBlue;
		palette.aEntries[x].peFlags=0;//指定调色板如何使用：PC_EXPLICIT（2）  PC_NOCOLLAPSE（4）  PC_RESERVED（1）	
	}
	hPalette=new CPalette;
	hPalette->CreatePalette((LPLOGPALETTE)&palette);//初始化调色板对象，
	return hPalette;
}

void CViewImage::OnDraw(CDC* pDC)//这个函数是一个必须要实现的虚函数，所以即使不大实用也要实现
{
	int m_scale=1;//控制缩放比例
	BYTE* pBitmapData=dib->GetData();//CDib类的指针对象，其内容还没有想好赋值
	LPBITMAPINFO pBitmapInfo=dib->GetInfo();
	int bitmapHeight=dib->GetHeight();
	int bitmapWidth=dib->GetWidth();
	int scaledWidth=(int)(bitmapWidth* m_scale);
	int scaledHeight=(int)(bitmapHeight* m_scale);
	if(dib->GetRGB())
	{
		CPalette* hPalette=CreateBitmapPalette(dib);//建立CPlalette对象并初始化调色板对象
		CPalette* hOldPalette=pDC->SelectPalette(hPalette,true);//为true表示后台调色板，将已创建的调色板调用到设备上下文中,并且返回旧的调色板
		//上面这个SelectPalette返回的就是老的调色板
		pDC->RealizePalette();//使调色板生效
		//前面加::表面调用的是win api，是全局函数，不是局部继承的函数
		::StretchDIBits(pDC->GetSafeHdc(),0,0,scaledWidth,scaledHeight,0,0,bitmapWidth,bitmapHeight,pBitmapData,pBitmapInfo,DIB_RGB_COLORS,SRCCOPY);
		              //设备上下文句柄
		pDC->SelectPalette(hOldPalette,true);
		::DeleteObject(hPalette);//释放关于hPalette调色板的一切资源（逻辑笔、画笔、字体、位图、区域或调色板）
	}
	else//24位真彩色
	{
		::StretchDIBits(pDC->GetSafeHdc(),0,0,scaledWidth,scaledHeight,0,0,bitmapWidth,bitmapHeight,pBitmapData,pBitmapInfo,DIB_RGB_COLORS,SRCCOPY);
	}

}

void CViewImage::OnDraw2(CDC* pDC,int x_move,int y_move)//这个才是我们需要用的绘制函数
{
	int m_scale=1;//控制缩放比例
	BYTE* pBitmapData=dib->GetData();//CDib类的指针对象
	LPBITMAPINFO pBitmapInfo=dib->GetInfo();
	int bitmapHeight=dib->GetHeight();
	int bitmapWidth=dib->GetWidth();
	int scaledWidth=(int)(bitmapWidth* m_scale);
	int scaledHeight=(int)(bitmapHeight* m_scale);
	if(dib->GetRGB())
	{
		CPalette* hPalette=CreateBitmapPalette(dib);//建立CPlalette对象并初始化调色板对象
		CPalette* hOldPalette=pDC->SelectPalette(hPalette,true);//为true表示后台调色板，将已创建的调色板调用到设备上下文中,并且返回旧的调色板
		//上面这个SelectPalette返回的就是老的调色板
		pDC->RealizePalette();//使调色板生效
		//前面加::表面调用的是win api，是全局函数，不是局部继承的函数
		::StretchDIBits(pDC->GetSafeHdc(),0+x_move,0+y_move,scaledWidth,scaledHeight,0,0,bitmapWidth,bitmapHeight,pBitmapData,pBitmapInfo,DIB_RGB_COLORS,SRCCOPY);
		              //设备上下文句柄
		pDC->SelectPalette(hOldPalette,true);
		::DeleteObject(hPalette);//释放关于hPalette调色板的一切资源（逻辑笔、画笔、字体、位图、区域或调色板）
	}
	else//24位真彩色
	{
		::StretchDIBits(pDC->GetSafeHdc(),0+x_move,0+y_move,scaledWidth,scaledHeight,0,0,bitmapWidth,bitmapHeight,pBitmapData,pBitmapInfo,DIB_RGB_COLORS,SRCCOPY);
	}

}

void CViewImage::OnDraw3(CDC *pDC,LPBYTE temp,int x_move,int y_move)
{
	int m_scale=1;//控制缩放比例
	//BYTE* pBitmapData=dib->GetData();//CDib类的指针对象
	LPBITMAPINFO pBitmapInfo=dib->GetInfo();
	int bitmapHeight=dib->GetHeight();
	int bitmapWidth=dib->GetWidth();
	int scaledWidth=(int)(bitmapWidth* m_scale);
	int scaledHeight=(int)(bitmapHeight* m_scale);
	if(dib->GetRGB())
	{
		CPalette* hPalette=CreateBitmapPalette(dib);//建立CPlalette对象并初始化调色板对象
		CPalette* hOldPalette=pDC->SelectPalette(hPalette,true);//为true表示后台调色板，将已创建的调色板调用到设备上下文中,并且返回旧的调色板
		//上面这个SelectPalette返回的就是老的调色板
		pDC->RealizePalette();//使调色板生效
		//前面加::表面调用的是win api，是全局函数，不是局部继承的函数
		::StretchDIBits(pDC->GetSafeHdc(),0+x_move,0+y_move,scaledWidth,scaledHeight,0,0,bitmapWidth,bitmapHeight,temp,pBitmapInfo,DIB_RGB_COLORS,SRCCOPY);
		              //设备上下文句柄
		pDC->SelectPalette(hOldPalette,true);
		::DeleteObject(hPalette);//释放关于hPalette调色板的一切资源（逻辑笔、画笔、字体、位图、区域或调色板）
	}
	else//24位真彩色
	{
		::StretchDIBits(pDC->GetSafeHdc(),0+x_move,0+y_move,scaledWidth,scaledHeight,0,0,bitmapWidth,bitmapHeight,temp,pBitmapInfo,DIB_RGB_COLORS,SRCCOPY);
	}

}

void CViewImage::OnDraw4(CDC *pDC,int x_move,int y_move,int need_width,int need_height)
{
	int m_scale=1;//控制缩放比例
	//BYTE* pBitmapData=dib->GetData();//CDib类的指针对象
	LPBITMAPINFO pBitmapInfo=dib->GetInfo();
	/*int bitmapHeight=dib->GetHeight();
	int bitmapWidth=dib->GetWidth();*/
	int scaledWidth=(int)(need_width* m_scale);
	int scaledHeight=(int)(need_height* m_scale);
	if(dib->GetRGB())
	{
		CPalette* hPalette=CreateBitmapPalette(dib);//建立CPlalette对象并初始化调色板对象
		CPalette* hOldPalette=pDC->SelectPalette(hPalette,true);//为true表示后台调色板，将已创建的调色板调用到设备上下文中,并且返回旧的调色板
		//上面这个SelectPalette返回的就是老的调色板
		pDC->RealizePalette();//使调色板生效
		//前面加::表面调用的是win api，是全局函数，不是局部继承的函数
		::StretchDIBits(pDC->GetSafeHdc(),0+x_move,0+y_move,scaledWidth,scaledHeight,0,0,need_width,need_height,dib->GetData(),pBitmapInfo,DIB_RGB_COLORS,SRCCOPY);
		              //设备上下文句柄
		pDC->SelectPalette(hOldPalette,true);
		::DeleteObject(hPalette);//释放关于hPalette调色板的一切资源（逻辑笔、画笔、字体、位图、区域或调色板）
	}
	else//24位真彩色
	{
		::StretchDIBits(pDC->GetSafeHdc(),0+x_move,0+y_move,scaledWidth,scaledHeight,0,0,need_width,need_height,dib->GetData(),pBitmapInfo,DIB_RGB_COLORS,SRCCOPY);
	}

}

void CViewImage::OnXiangxia(CDC *pDC)//向下扫描
{
	//CDC *pDC=GetDC();
	
//	clearmem();//复制图像数据，取得原始图像的拷贝文件？？？找不到
	CDocument *pDoc=GetDocument();//返回与本视图连接的文档类对象指针,这边改了

	//ASSERT_VALID(pDoc);//判断指向的对象是否为空，debug下有效
	//if(!pDoc->stateddoc&&state2==1)//???????????
	//{
		BYTE* pBitmapData=dib->GetData();//将书中的伪变量换成了自己设的
		LPBITMAPINFO pBitmapInfo=dib->GetInfo();
		int bitmapHeight=dib->GetHeight();
		int bitmapWidth=dib->GetWidth();

		if(dib->GetRGB())//如果颜色表指针不为空
		{
			CRect rect(bitmapWidth+5,0,2*bitmapWidth+5,bitmapHeight);//一个矩形类
			CBrush brush(RGB(255,255,255));
			pDC->FillRect(&rect,&brush);//将整个矩阵用白色填满，图像的区域是不包含右边和下边

			CPalette* hPalette=CreateBitmapPalette(dib);
			CPalette* hOldPalette=pDC->SelectPalette(hPalette,true);
			pDC->RealizePalette();
			for(int j=0;j<bitmapHeight;j++)
			{
				//修改了第7个参数，比原书-1，书那样是不对的
				//图像横着是x轴，竖着向下是y轴
				::StretchDIBits(pDC->GetSafeHdc(),bitmapWidth+5,j,bitmapWidth,1,0,bitmapHeight-j-1,bitmapWidth,1,pBitmapData,pBitmapInfo,DIB_RGB_COLORS,SRCCOPY);
				//1是设备上下文句柄，2、3参数是绘制图像左上角坐标，4、5是绘制图像的宽度和高度，6、7是要绘制的原图的左下角坐标（--假如坐标超出了，绘制图像相应区域会以白色代替--）（注意，位图行的存储是颠倒的，所以是倒着复制），8、9是原图宽度和高度，10是指向图像数据的指针，11是指向图像BITMAPINFO结构的指针，12是bmiColors包含真实的RGB值还是调色板中的索引值，13指定要进行的光栅运算
				//如果目标矩阵大于要复制的原图区域就进行行和列的拉伸，反之利用光栅操作进行压缩
				Sleep(5);//延时5毫秒
			}
			pDC->SelectPalette(hOldPalette,true);
			::DeleteObject(hPalette);
		}
//	}
	//Invalidate();//刷新，调用会出现中断
}
void CViewImage::OnXiangshang(CDC *pDC)//向上扫描
{
	//CDocument *pDoc=GetDocument();
	BYTE* pBitmapData=dib->GetData();
	LPBITMAPINFO pBitmapInfo=dib->GetInfo();
	int bitmapHeight=dib->GetHeight();
	int bitmapWidth=dib->GetWidth();

	if(dib->GetRGB())
	{
		CRect rect(bitmapWidth+5,0,bitmapWidth*2+5,bitmapHeight);//一个矩形类
		CBrush brush(RGB(255,255,255));
		pDC->FillRect(&rect,&brush);//将整个矩阵用白色填满，但是只包括矩阵的左上边界，不包括右下边界

		CPalette* hPalette=CreateBitmapPalette(dib);
		CPalette* hOldPalette=pDC->SelectPalette(hPalette,true);
		pDC->RealizePalette();
		for(int j=0;j<bitmapHeight;j++)
		{
			
			::StretchDIBits(pDC->GetSafeHdc(),bitmapWidth+5,bitmapHeight-j-1,bitmapWidth,1,0,j,bitmapWidth,1,pBitmapData,pBitmapInfo,DIB_RGB_COLORS,SRCCOPY);
			Sleep(5);
		}
		pDC->SelectPalette(hOldPalette,true);
		::DeleteObject(hPalette);
	}
}
void CViewImage::OnXiangyou(CDC *pDC)//向右扫描
{
	//CDocument *pDoc=GetDocument();
	BYTE* pBitmapData=dib->GetData();
	LPBITMAPINFO pBitmapInfo=dib->GetInfo();
	int bitmapHeight=dib->GetHeight();
	int bitmapWidth=dib->GetWidth();

	if(dib->GetRGB())
	{

		CRect rect(bitmapWidth+5,0,2*bitmapWidth+5,bitmapHeight);
		CBrush brush(RGB(255,255,255));
		pDC->FillRect(&rect,&brush);

		CPalette *hPalette=CreateBitmapPalette(dib);
		CPalette *hOldPalette=pDC->SelectPalette(hPalette,true);
		pDC->RealizePalette();
		for(int i=0;i<bitmapWidth;i++)
		{
			::StretchDIBits(pDC->GetSafeHdc(),i+bitmapWidth+5,0,1,bitmapHeight,i,0,1,bitmapHeight,pBitmapData,pBitmapInfo,DIB_RGB_COLORS,SRCCOPY);
			Sleep(5);
		}
		pDC->SelectPalette(hOldPalette,true);
		::DeleteObject(hPalette);
	}
}
void CViewImage::OnXiangzuo(CDC *pDC)//向左扫描
{
	//CDocument *pDoc=GetDocument();
	BYTE* pBitmapData=dib->GetData();
	LPBITMAPINFO pBitmapInfo=dib->GetInfo();
	int bitmapHeight=dib->GetHeight();
	int bitmapWidth=dib->GetWidth();

	if(dib->GetRGB())
	{
		CRect rect(bitmapWidth+5,0,2*bitmapWidth+5,bitmapHeight);
		CBrush brush(RGB(255,255,255));
		pDC->FillRect(&rect,&brush);

		CPalette* hPalette=CreateBitmapPalette(dib);
		CPalette *hOldPalette=pDC->SelectPalette(hPalette,true);
		pDC->RealizePalette();
		for(int i=0;i<bitmapWidth;i++)
		{
			::StretchDIBits(pDC->GetSafeHdc(),2*bitmapWidth-i+4,0,1,bitmapHeight,bitmapWidth-i-1,0,1,bitmapHeight,pBitmapData,pBitmapInfo,DIB_RGB_COLORS,SRCCOPY);
			Sleep(5);
		}
		pDC->SelectPalette(hOldPalette,true);
		::DeleteObject(hPalette);
	}
}
void CViewImage::ToShuiPingYouYi(CDC *pDC)//水平右移
{
	//CDocument *pDoc=GetDocument();

	BYTE* pBitmapData=dib->GetData();
	LPBITMAPINFO pBitmapInfo=dib->GetInfo();
	int bitmapHeight=dib->GetHeight();
	int bitmapWidth=dib->GetWidth();

	if(dib->GetRGB())
	{
		CRect rect(bitmapWidth+5,0,2*bitmapWidth+5,bitmapHeight);
		CBrush brush(RGB(255,255,255));
		pDC->FillRect(&rect,&brush);

		CPalette *hPalette=CreateBitmapPalette(dib);
		CPalette *hOldPalette=pDC->SelectPalette(hPalette,true);
		pDC->RealizePalette();
		
		for(int i=0;i<bitmapWidth;i++)
		{
			//原书这个代码是错误的，图像下部分没有复制到，因为当j小于bitmapHeight而又距离小于8时，下一次就不能复制了
			/*for(int j=0;j<bitmapHeight;j=j+8)
			{
				::StretchDIBits(pDC->GetSafeHdc(),bitmapWidth+5,j-8,i+1,8,bitmapWidth-i,bitmapHeight-j,i+1,8,pBitmapData,pBitmapInfo,DIB_RGB_COLORS,SRCCOPY);
			}*/
			//按照自己理解写的，简单又实用
			::StretchDIBits(pDC->GetSafeHdc(),bitmapWidth+5,0,i+1,bitmapHeight,bitmapWidth-i-1,0,i+1,bitmapHeight,pBitmapData,pBitmapInfo,DIB_RGB_COLORS,SRCCOPY);
			Sleep(3);
		}

		pDC->SelectPalette(hOldPalette,true);
		::DeleteObject(hPalette);
	}
}
void CViewImage::ToChuiZhiShangYi(CDC *pDC)//垂直向上
{
	//CDocument *pDoc=GetDocument();

	BYTE* pBitmapData=dib->GetData();
	LPBITMAPINFO pBitmapInfo=dib->GetInfo();
	int bitmapHeight=dib->GetHeight();
	int bitmapWidth=dib->GetWidth();

	if(dib->GetRGB())
	{
		CRect rect(bitmapWidth+5,0,2*bitmapWidth+5,bitmapHeight);
		CBrush brush(RGB(255,255,255));
		pDC->FillRect(&rect,&brush);

		CPalette *hPalette=CreateBitmapPalette(dib);
		CPalette *hOldPalette=pDC->SelectPalette(hPalette,true);
		pDC->RealizePalette();

		for(int j=0;j<bitmapHeight;j++)
		{
			::StretchDIBits(pDC->GetSafeHdc(),bitmapWidth+5,bitmapHeight-j-1,bitmapWidth,j+1,0,bitmapHeight-1-j,bitmapWidth,j+1,pBitmapData,pBitmapInfo,DIB_RGB_COLORS,SRCCOPY);
			Sleep(4);
		}

		pDC->SelectPalette(hOldPalette,true);
		::DeleteObject(hPalette);
	}
}
void CViewImage::ToJiaoChaFeiRu(CDC *pDC)//交叉飞入
{
	//CDocument *pDoc=GetDocument();

	BYTE* pBitmapData=dib->GetData();
	LPBITMAPINFO pBitmapInfo=dib->GetInfo();
	int bitmapHeight=dib->GetHeight();
	int bitmapWidth=dib->GetWidth();

	if(dib->GetRGB())
	{
		CRect rect(bitmapWidth+5,0,2*bitmapWidth+5,bitmapHeight);
		CBrush brush(RGB(255,255,255));
		pDC->FillRect(&rect,&brush);

		CPalette *hPalette=CreateBitmapPalette(dib);
		CPalette *hOldPalette=pDC->SelectPalette(hPalette,true);
		pDC->RealizePalette();
		
		for(int i=0;i<bitmapWidth;i++)
		{
				::StretchDIBits(pDC->GetSafeHdc(),bitmapWidth+5,0,i+1,bitmapHeight/2,bitmapWidth-i-1,bitmapHeight/2,i+1,bitmapHeight/2,pBitmapData,pBitmapInfo,DIB_RGB_COLORS,SRCCOPY);
				::StretchDIBits(pDC->GetSafeHdc(),bitmapWidth*2+4-i,bitmapHeight/2,i+1,bitmapHeight-bitmapHeight/2,0,0,i+1,bitmapHeight-bitmapHeight/2,pBitmapData,pBitmapInfo,DIB_RGB_COLORS,SRCCOPY);
				Sleep(3);
		}

		pDC->SelectPalette(hOldPalette,true);
		::DeleteObject(hPalette);
	}
}
void CViewImage::ToSiZhouKuoZhang(CDC *pDC)//中间扩张
{
	//CDocument *pDoc=GetDocument();
	BYTE* pBitmapData=dib->GetData();
	LPBITMAPINFO pBitmapInfo=dib->GetInfo();
	int bitmapHeight=dib->GetHeight();
	int bitmapWidth=dib->GetWidth();

	if(dib->GetRGB())
	{
		CRect rect(bitmapWidth+5,0,2*bitmapWidth+5,bitmapHeight);
		CBrush brush(RGB(255,255,255));
		pDC->FillRect(&rect,&brush);

		CPalette* hPalette=CreateBitmapPalette(dib);
		CPalette* hOldPalette=pDC->SelectPalette(hPalette,true);
		pDC->RealizePalette();

		//for(int i=1;i<=bitmapWidth/2;i++)//直接从1开始
		//{
		//	//第一个完全多余，而且函数是错误的，竖长型的图片是不能伸展完全的
		//	//::StretchDIBits(pDC->GetSafeHdc(),bitmapWidth+5+bitmapWidth/2-i,bitmapHeight/2-i,i*2,i,bitmapWidth/2-i,bitmapHeight/2-i,i*2,i,pBitmapData,pBitmapInfo,DIB_RGB_COLORS,SRCCOPY);
		//	::StretchDIBits(pDC->GetSafeHdc(),bitmapWidth+5+bitmapWidth/2-i,bitmapHeight/2-i,i*2,i*2,bitmapWidth/2-i,bitmapHeight/2-i,i*2,i*2,pBitmapData,pBitmapInfo,DIB_RGB_COLORS,SRCCOPY);
		//	Sleep(30);
		//}
		int u,d,l,r;//上、下、左、右边界值
		if(bitmapHeight%2)
		{
			u=bitmapHeight/2+1;
			d=bitmapHeight/2-1;
		}
		else
		{
			u=bitmapHeight/2;
			d=bitmapHeight/2-1;
		}
		if(bitmapWidth%2)
		{
			l=bitmapWidth/2+1;
			r=bitmapWidth/2-1;
		}
		else
		{
			l=bitmapWidth/2;
			r=bitmapWidth/2-1;
		}
		do
		{	
			u=u-1>=0?u-1:0;
			d=d+1<bitmapHeight?d+1:bitmapHeight-1;
			l=l-1>=0?l-1:0;
			r=r+1<bitmapWidth?r+1:bitmapWidth-1;
			::StretchDIBits(pDC->GetSafeHdc(),bitmapWidth+5+l,u,r-l+1,d-u+1,l,u,r-l+1,d-u+1,pBitmapData,pBitmapInfo,DIB_RGB_COLORS,SRCCOPY);
			Sleep(10);
		}while(!(u==0&&l==0&&d==bitmapHeight-1&&r==bitmapWidth-1));

		pDC->SelectPalette(hOldPalette,true);
		::DeleteObject(hPalette);
	}
}
void CViewImage::ToZhongJianShouSuo(CDC *pDC)
{
	//CDocument *pDoc=GetDocument();
	BYTE* pBitmapData=dib->GetData();
	LPBITMAPINFO pBitmapInfo=dib->GetInfo();
	int bitmapHeight=dib->GetHeight();
	int bitmapWidth=dib->GetWidth();

	if(dib->GetRGB())
	{
		CRect rect(bitmapWidth+5,0,2*bitmapWidth+5,bitmapHeight);
		CBrush brush(RGB(255,255,255));
		pDC->FillRect(&rect,&brush);

		CPalette* hPalette=CreateBitmapPalette(dib);
		CPalette* hOldPalette=pDC->SelectPalette(hPalette,true);
		pDC->RealizePalette();

		for(int j=0;j<bitmapHeight/2+bitmapHeight%2;j++)//解决奇数的时候中间不能写的问题
		{
			//又是个不完全正确显示代码。。。。有修改
			//分别从上下向中间复制
			::StretchDIBits(pDC->GetSafeHdc(),bitmapWidth+5,j,bitmapWidth,1,0,bitmapHeight-j-1,bitmapWidth,1,pBitmapData,pBitmapInfo,DIB_RGB_COLORS,SRCCOPY);
			::StretchDIBits(pDC->GetSafeHdc(),bitmapWidth+5,bitmapHeight-j-1,bitmapWidth,1,0,j,bitmapWidth,1,pBitmapData,pBitmapInfo,DIB_RGB_COLORS,SRCCOPY);
			Sleep(10);
		}
		pDC->SelectPalette(hOldPalette,true);
		::DeleteObject(hPalette);
	}
}
void CViewImage::ToShuiPingShanTiao(CDC *pDC)//水平栅条
{
	//CDocument *pDoc=GetDocument();
	BYTE* pBitmapData=dib->GetData();
	LPBITMAPINFO pBitmapInfo=dib->GetInfo();
	int bitmapHeight=dib->GetHeight();
	int bitmapWidth=dib->GetWidth();

	if(dib->GetRGB())
	{
		CRect rect(bitmapWidth+5,0,2*bitmapWidth+5,bitmapHeight);
		CBrush brush(RGB(255,255,255));
		pDC->FillRect(&rect,&brush);

		CPalette* hPalette=CreateBitmapPalette(dib);
		CPalette* hOldPalette=pDC->SelectPalette(hPalette,true);
		pDC->RealizePalette();

		int scanline=5;//每条栅条的宽度
		int k=0;
		for(int i=0;i<bitmapWidth;i++)
		{
			for(int j=0;j<bitmapHeight;j+=2*scanline)
			{
				//按照代码的实现效果来看，虽然我并没有加边界判断条件，但是它好像只会复制到有数据的地方，不用判断边界
				::StretchDIBits(pDC->GetSafeHdc(),bitmapWidth+5,j,i+1,scanline,bitmapWidth-i-1,bitmapHeight-j-scanline,i+1,scanline,pBitmapData,pBitmapInfo,DIB_RGB_COLORS,SRCCOPY);
				k=j+scanline;//右侧栅条起始行
				::StretchDIBits(pDC->GetSafeHdc(),2*bitmapWidth+4-i,k,i+1,scanline,0,bitmapHeight-k-scanline,i+1,scanline,pBitmapData,pBitmapInfo,DIB_RGB_COLORS,SRCCOPY);				
			}
			Sleep(5);
		}
		pDC->SelectPalette(hOldPalette,true);
		::DeleteObject(hOldPalette);
	}
}
void CViewImage::TOShuZhiShanTiao(CDC *pDC)//竖直栅条
{
	//CDocument *pDoc=GetDocument();
	BYTE* pBitmapData=dib->GetData();
	LPBITMAPINFO pBitmapInfo=dib->GetInfo();
	int bitmapHeight=dib->GetHeight();
	int bitmapWidth=dib->GetWidth();
	if(dib->GetRGB())
	{
		CRect rect(bitmapWidth+5,0,2*bitmapWidth+5,bitmapHeight);
		CBrush brush(RGB(255,255,255));
		pDC->FillRect(&rect,&brush);

		CPalette *hPalette=CreateBitmapPalette(dib);
		CPalette* hOldPalette=pDC->SelectPalette(hPalette,true);
		pDC->RealizePalette();
		int scanline=5;
		int k=0;
		for(int j=0;j<bitmapHeight;j++)
		{
			for(int i=0;i<bitmapWidth;i+=2*scanline)
			{
				::StretchDIBits(pDC->GetSafeHdc(),bitmapWidth+5+i,0,scanline,j+1,i,0,scanline,j+1,pBitmapData,pBitmapInfo,DIB_RGB_COLORS,SRCCOPY);
				k=i+scanline;
				::StretchDIBits(pDC->GetSafeHdc(),bitmapWidth+5+k,bitmapHeight-1-j,scanline,j+1,k,bitmapHeight-1-j,scanline,j+1,pBitmapData,pBitmapInfo,DIB_RGB_COLORS,SRCCOPY);
			
			}
			Sleep(5);
		}
		pDC->SelectPalette(hOldPalette,true);
		::DeleteObject(hPalette);
	}
}
void CViewImage::ToTuXiangJianXian(CDC *pDC)//图像渐显
{
	//CDocument *pDoc=GetDocument();
	BYTE* pBitmapData=dib->GetData();
	LPBITMAPINFO pBitmapInfo=dib->GetInfo();
	int bitmapHeight=dib->GetHeight();
	int bitmapWidth=dib->GetWidth();
	if(dib->GetRGB())
	{
		CRect rect(bitmapWidth+5,0,2*bitmapWidth+5,bitmapHeight);
		CBrush brush(RGB(255,255,255));
		pDC->FillRect(&rect,&brush);

		CPalette *hPalette=CreateBitmapPalette(dib);
		CPalette* hOldPalette=pDC->SelectPalette(hPalette,true);
		pDC->RealizePalette();
		
		LPBYTE temp,temp1,temp2;//temp指向新图像矩阵原始指针
		temp=new BYTE[bitmapHeight*bitmapWidth];
		memset(temp,0,bitmapHeight*bitmapWidth);
		for(int n=0;n<=256;n++)
		{
			temp1=temp;
			temp2=pBitmapData;
			for(int i=0;i<bitmapWidth;i++)
				for(int j=0;j<bitmapHeight;j++)
				{
					*temp1=(*temp2)*n/256;//这种写法我还是第一次
					temp2++;
					temp1++;
				}
				::StretchDIBits(pDC->GetSafeHdc(),bitmapWidth+5,0,bitmapWidth,bitmapHeight,0,0,bitmapWidth,bitmapHeight,temp,pBitmapInfo,DIB_RGB_COLORS,SRCCOPY);
				Sleep(6);
		}

		pDC->SelectPalette(hOldPalette,true);
		::DeleteObject(hPalette);
		delete[]temp;
	}
}
void CViewImage::ToShuiPingBaiYeChuang(CDC* pDC)//水平百叶窗
{
	//CDocument *pDoc=GetDocument();
	BYTE* pBitmapData=dib->GetData();
	LPBITMAPINFO pBitmapInfo=dib->GetInfo();
	int bitmapHeight=dib->GetHeight();
	int bitmapWidth=dib->GetWidth();
	if(dib->GetRGB())
	{
		CRect rect(bitmapWidth+5,0,2*bitmapWidth+5,bitmapHeight);
		CBrush brush(RGB(255,255,255));
		pDC->FillRect(&rect,&brush);

		CPalette *hPalette=CreateBitmapPalette(dib);
		CPalette* hOldPalette=pDC->SelectPalette(hPalette,true);
		pDC->RealizePalette();
		//按照原书的根本就不能完全形成，有裂缝,已修改
		for(int i=0;i<bitmapWidth/10;i++)
			for(int j=0;j<=10;j++)//有=是最后那个不足10份的不能落下
			{
				::StretchDIBits(pDC->GetSafeHdc(),bitmapWidth+5+j*(bitmapWidth/10),0,i+1,bitmapHeight,j*(bitmapWidth/10),0,i+1,bitmapHeight,pBitmapData,pBitmapInfo,DIB_RGB_COLORS,SRCCOPY);
				Sleep(1);
			}
	
		pDC->SelectPalette(hOldPalette,true);
		::DeleteObject(hPalette);
	}
}
void CViewImage::ToShuZhiBaiYeChuang(CDC* pDC)//垂直百叶窗
{
	//CDocument *pDoc=GetDocument();
	BYTE* pBitmapData=dib->GetData();
	LPBITMAPINFO pBitmapInfo=dib->GetInfo();
	int bitmapHeight=dib->GetHeight();
	int bitmapWidth=dib->GetWidth();
	if(dib->GetRGB())
	{
		CRect rect(bitmapWidth+5,0,2*bitmapWidth+5,bitmapHeight);
		CBrush brush(RGB(255,255,255));
		pDC->FillRect(&rect,&brush);

		CPalette *hPalette=CreateBitmapPalette(dib);
		CPalette* hOldPalette=pDC->SelectPalette(hPalette,true);
		pDC->RealizePalette();
		//按照原书的根本就不能完全形成，有裂缝,已修改,注意加上括号了
		for(int j=0;j<bitmapHeight/10;j++)
			for(int i=0;i<=10;i++)//有=是最后那个不足10份的不能落下
			{
				::StretchDIBits(pDC->GetSafeHdc(),bitmapWidth+5,i*(bitmapHeight/10),bitmapWidth,j+1,0,bitmapHeight-(i+1)*(bitmapHeight/10),bitmapWidth,j+1,pBitmapData,pBitmapInfo,DIB_RGB_COLORS,SRCCOPY);
				Sleep(1);
			}
	
		pDC->SelectPalette(hOldPalette,true);
		::DeleteObject(hPalette);
	}
}
void CViewImage::ToMaSaiKeXianShi(CDC *pDC)//马赛克显示
{
	//CDocument *pDoc=GetDocument();
	BYTE* pBitmapData=dib->GetData();
	LPBITMAPINFO pBitmapInfo=dib->GetInfo();
	int bitmapHeight=dib->GetHeight();
	int bitmapWidth=dib->GetWidth();
	long mx=0;
	long my=0;
	//int scanline=8;//设置显示定位量
	int k=0;
	int nrw=0;
	int nrh=0;
	if((bitmapWidth%12)!=0) nrw=1;//方格宽是12，多出来的不够12可以作为一个单独显示
	if((bitmapHeight%12)!=0) nrh=1;
	long ltilenum=(bitmapWidth/12+nrw)*(bitmapHeight/12+nrh);
	POINT *point=new POINT[ltilenum];

	if(dib->GetRGB())
	{
		CRect rect(bitmapWidth+5,0,2*bitmapWidth+5,bitmapHeight);
		CBrush brush(RGB(255,255,255));
		pDC->FillRect(&rect,&brush);

		CPalette *hPalette=CreateBitmapPalette(dib);
		CPalette* hOldPalette=pDC->SelectPalette(hPalette,true);
		pDC->RealizePalette();
		//
		for(int mi=0;mi<ltilenum;mi++)//方框总数
		{
			point[mi].x=mx;
			point[mi].y=my;
			mx=mx+12;
			if(mx>=bitmapWidth)//修改了
			{
				mx=0;my=my+12;
			}
		}
		//srand((unsigned)time(NULL));//设定随机数种子
		//代码不能完全显示，已修改
		//for(int i=0;i<=2;i++)
		//{
		//	//
		//	for(int mi=ltilenum-1;mi>=0;mi--)
		//	{
		//		int n=(int)((double)ltilenum*rand()/RAND_MAX);
		//		mx=point[n].x;
		//		my=point[n].y;
		//		::StretchDIBits(pDC->GetSafeHdc(),bitmapWidth+5+mx,my,12,12,mx,bitmapHeight-my-12,12,12,pBitmapData,pBitmapInfo,DIB_RGB_COLORS,SRCCOPY);
		//		point[n].x=point[mi].x;//使已经显示过的指向可能还没显示的
		//		point[n].y=point[mi].y;
		//		Sleep(1);
		//	}
		//}
		//下面是我的解法，记录了显示的数，减少重复和避免没有显示完全图像
	    int xianshi=0;
		int *t=new int[ltilenum];
		memset(t,0,ltilenum*sizeof(int));//0表示没有访问过
		srand((unsigned)time(NULL));//加上这个反而出不来了
		while(xianshi<ltilenum)
		{
				int n=(int)((double)ltilenum*rand()/RAND_MAX);
				n=n==ltilenum?ltilenum-1:n;
			    if(t[n]==0)
				{
				mx=point[n].x;
				my=point[n].y;
				::StretchDIBits(pDC->GetSafeHdc(),bitmapWidth+5+mx,my,12,12,mx,bitmapHeight-my-12,12,12,pBitmapData,pBitmapInfo,DIB_RGB_COLORS,SRCCOPY);
			    t[n]=1;
				xianshi++;
				Sleep(1);
				}
		}

		pDC->SelectPalette(hOldPalette,true);
		::DeleteObject(hPalette);
		delete[]point;
	}
}
