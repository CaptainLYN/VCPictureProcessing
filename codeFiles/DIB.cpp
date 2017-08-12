#include"stdafx.h"
#include"CDib.h"
#include<WindowsX.h>
#define WIDTHBYTES(bits) (((bits)+31)/32*4)  //用前面一个代替后面的
CDib::CDib()
{
	 
}
CDib::~CDib()
{
	GlobalFreePtr(m_pBitmapInfo);//释放在loadfile函数中在堆中申请的资源
}
void CDib::LoadFile(CString m_filename)//静态不允许修改
{
	//strcpy(m_fileName,dibFileName);
	CFile dibFile(m_filename,CFile::modeRead);//构造函数初始化，制度打开文件,LPCTSTR就是const char*,unicode通用字符集
	dibFile.Read((void*)&bitmapFileHeader,sizeof(BITMAPFILEHEADER));
	if(bitmapFileHeader.bfType==0x4d42)//位图文件的类型，就是十进制19778
	{
		DWORD fileLength=dibFile.GetLength();
		/*DWORD*/ size=fileLength-sizeof(BITMAPFILEHEADER);//图像内容的实际大小+颜色表+位图文件信息头
		/*BYTE**/ pDib=(BYTE*)GlobalAllocPtr(GMEM_MOVEABLE,size);//从堆中分配属性为GMEM_MOVEABLE（win32平台和GMEM_FIXED固定的已经没有大区别）、size大小的可移动内存
		dibFile.Read((void*)pDib,size);//从上述关联的文件中读取size大小的数据放入指针缓冲区，每读一次读取指针的位置移动size大小，文件头已经读取过了，这是包含信息头的数据
		dibFile.Close();

		m_pBitmapInfo=(BITMAPINFO*)pDib;//现在它指向的就是位图信息，也是位图信息的第一个成员的位置
		m_pBitmapInfoHeader=(BITMAPINFOHEADER*)pDib;
		m_pRGB=(RGBQUAD*)(pDib+m_pBitmapInfoHeader->biSize);//指向颜色表
		int m_numberOfColors=GetNumberOfColors();//2、16、256或者是真彩色
		if(m_pBitmapInfoHeader->biClrUsed==0)//位图实际使用的颜色表中的颜色数是不对的，就修改
			m_pBitmapInfoHeader->biClrUsed=m_numberOfColors;
		DWORD colorTableSize=m_numberOfColors*sizeof(RGBQUAD);//调色板的大小
		m_pData=pDib+m_pBitmapInfoHeader->biSize+colorTableSize;//颜色数据的真正起始位置
		if(m_pRGB==(RGBQUAD*)m_pData)//如果没有调色板
			m_pRGB=NULL;
		m_pBitmapInfoHeader->biSizeImage=GetSize();//位图的大小，以字节为单位
		m_valid=TRUE;
	}
	else
	{
		m_valid=FALSE;
		MessageBox(NULL,_T("这不是位图文件！"),_T("提示"),MB_OK);//这里做了修改，关于书
	}
}

BOOL CDib::IsValid()
{
	return m_valid;
}

char*CDib::GetFileName()
{
	return m_fileName;
}

UINT CDib::GetWidth()
{
	return (UINT)m_pBitmapInfoHeader->biWidth;
}

UINT CDib::GetHeight()
{
	return (UINT)m_pBitmapInfoHeader->biHeight;
}

DWORD CDib::GetSize()
{
	if(m_pBitmapInfoHeader->biSizeImage!=0)//位图的大小
		return m_pBitmapInfoHeader->biSizeImage;
	else
	{//不对就自己计算
		DWORD height=(DWORD)GetHeight();
		DWORD width=(DWORD)GetWidth();
		return height*/*width */GetDibWidthBytes();
	}
}


//返回行字节数
DWORD CDib::GetDibWidthBytes()
{
	byBitCount=m_pBitmapInfoHeader->biBitCount;//每个像素所需的位数：1、4、8、真彩色
	LONG nWidth=m_pBitmapInfoHeader->biWidth;//位图的宽度，以像素为单位

	dwWidthBytes=(DWORD)m_pBitmapInfoHeader->biWidth;//位图的宽度字节数
	if(byBitCount==1) dwWidthBytes=(nWidth+7)/8;//一位像素，那按字节计算就应该除8
	else if(byBitCount==4) dwWidthBytes=(nWidth+1)/2;
	else if(byBitCount==24) dwWidthBytes=nWidth*3;//因为真彩色每个像素是24位

	while((dwWidthBytes&3)!=0) dwWidthBytes++;//是否为4的倍数，因为位图每行为4的倍数，不足补0

	return dwWidthBytes;
}

//返回位图颜色数目
UINT CDib::GetNumberOfColors()
{
	int numberOfColors;

	if((m_pBitmapInfoHeader->biClrUsed==0)&&(m_pBitmapInfoHeader->biBitCount<9))
	{
		switch(m_pBitmapInfoHeader->biBitCount)
		{
		case 1:numberOfColors=2;break;
		case 4:numberOfColors=16;break;
		case 8:numberOfColors=256;
		}
	}
	else
		numberOfColors=(int)m_pBitmapInfoHeader->biClrUsed;//如果是真彩色，就是实际使用的颜色
	return numberOfColors;
}

BYTE* CDib::GetData()
{
	return m_pData;
}

BYTE* CDib::GetData2()
{
	if(GetRGB())
		m_pData2=m_pData;//有颜色表的情况下两个相同
	return m_pData2;
}

RGBQUAD* CDib::GetRGB()
{
	return m_pRGB;
}

BITMAPINFO* CDib::GetInfo()
{
	return m_pBitmapInfo;//位图信息指针
}

WORD CDib::PaletteSize(LPBYTE lpDIB)//LPBYTE是BYTE指针
{
	return (DIBNumColors(lpDIB)*sizeof(RGBQUAD/*RGBTRIPLE*/));//位图指针指向的颜色的数目*每一个颜色的大小,颜色表的位总大小
}

//应该是返回颜色表中的数据项数
WORD CDib::DIBNumColors(LPBYTE lpDIB)
{
	WORD wBitCount;//设备无关图的位数
	//wBitCount=((LPBITMAPCOREHEADER)lpDIB)->bcBitCount;//每个颜色的位数
	wBitCount=((LPBITMAPINFOHEADER)lpDIB)->biBitCount;
	switch(wBitCount)
	{
	case 1:return 2;
	case 4:return 16;
	case 8:return 256;
	default:return 0;
	}
}

void CDib::SaveFile(const CString filename)
{
	BITMAPFILEHEADER bmfHdr;
	LPBITMAPINFOHEADER lpBI;
	DWORD dwDIBSize;

	bmfHdr.bfType=0x4d42;//"BM"
	lpBI=(LPBITMAPINFOHEADER)m_pBitmapInfoHeader;

	dwDIBSize=*(LPDWORD)lpBI+PaletteSize((LPBYTE)lpBI);//位图数据和信息头+颜色表的位大小，这里只有后两部分
	//       本结构所占用字节数
	if((lpBI->biCompression==BI_RLE8)||(lpBI->biCompression==BI_RLE4))
		dwDIBSize+=lpBI->biSizeImage;//位图的大小字节
	else
	{
		DWORD dwBmBitSize;//只表示位图的位的大小
		dwBmBitSize=WIDTHBYTES((lpBI->biWidth)*((DWORD)lpBI->biBitCount))*lpBI->biHeight;//宽度的字节数*高度
		dwDIBSize+=dwBmBitSize;
		lpBI->biSizeImage=dwBmBitSize;//位图数据大小的字节数
	}
	bmfHdr.bfSize=dwDIBSize+sizeof(BITMAPFILEHEADER);//位图文件的大小，指的是整个文件
	bmfHdr.bfReserved1=0;
	bmfHdr.bfReserved2=0;
	bmfHdr.bfOffBits=(DWORD)sizeof(BITMAPFILEHEADER)+lpBI->biSize+PaletteSize((LPBYTE)lpBI);

	CFile dibFile(filename,CFile::modeWrite|CFile::modeCreate);//|是位或,CFile::modeWrite|CFile::modeCreate？？？？？？
	dibFile.Write(&bmfHdr,sizeof(BITMAPFILEHEADER));//这里必须要写两次，但是不知道为什么
	dibFile.Write(lpBI,dwDIBSize);
	dibFile.Close();
}

//rgb转成灰度图
void CDib::RGBtoGrade()
{
	if(GetRGB())//如果有颜色表，即不是真彩色24位
		m_pData2=m_pData;//颜色组号就是颜色，rgb相等
	else
	{
		BYTE r,g,b;
		int height,wide,size;
		height=GetHeight();
		wide=GetWidth();
		size=height*wide;
		m_pData2=(BYTE*)GlobalAllocPtr(GMEM_MOVEABLE,size);
		LONG lLineBytes=GetDibWidthBytes();
		for(int j=0;j<height;j++)
		{
			for(int i=0;i<wide;i++)
			{
				b=m_pData[j*lLineBytes+3*i];
				g=m_pData[j*lLineBytes+3*i+1];
				r=m_pData[j*lLineBytes+3*i+2];
				m_pData2[j*wide+i]=(BYTE)(0.3*r+0.59*g+0.11*b);//wide是像素，一个像素是24位，所以三个rgb映射一个像素值，rgb给予不同的权重，一个值就代表了rgb三个值，因为是灰度图
			}
		}
	}
}

//灰度图转为rgb
void CDib::GradetoRGB()
{
	if(GetRGB())
		m_pData=m_pData2;//反正rgb相等就是了
	else
	{
		//BYTE r,g,b;
		int height,wide;
		height=GetHeight();
		wide=GetWidth();
		LONG lLineBytes=GetDibWidthBytes();
		for(int j=0;j<height;j++)
		{
			for(int i=0;i<wide;i++)//将一个灰度值赋值给三个rgb，从最后一行开始，从一开始应该也是一样的
			{
				m_pData[(height-j-1)*lLineBytes+3*i]=m_pData2[(height-1-j)*wide+i];
				m_pData[(height-j-1)*lLineBytes+3*i+1]=m_pData2[(height-1-j)*wide+i];
				m_pData[(height-j-1)*lLineBytes+3*i+3]=m_pData2[(height-1-j)*wide+i];
			}
		}
	}
}