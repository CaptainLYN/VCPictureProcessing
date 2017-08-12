/*
#ifndef _CDIB_H_  //代表这个头文件里的变量只编译一次
#define _CDIB_H_
*/
#pragma once

class CDib:public CObject
{
public:
	RGBQUAD* m_pRGB;//颜色表指针
	BYTE* m_pData,*m_pData2;//m_pData指向原数据，m_pData2指向灰度数据
	UINT m_numberOfColors;//位图颜色数目
	BOOL m_valid;//是否载入了位图文件
	BITMAPFILEHEADER bitmapFileHeader;//位图文件头
	
	BITMAPINFOHEADER* m_pBitmapInfoHeader;//位图信息头
	BITMAPINFO* m_pBitmapInfo;//位图信息指针
	int byBitCount;
	DWORD dwWidthBytes;//DWORD 就是Double Word,4个字节，32位，位图的宽度字节数
	BYTE* pDib;//文件中位图总数据指针，也就是读入内存所以数据的第一个
	DWORD size;//位图总数据的长度

public:
	CDib();
	~CDib();

	char m_fileName[256];//文件名
	char* GetFileName();
	BOOL IsValid();//是否载入了位图文件
	DWORD GetSize();
	UINT GetWidth();
	UINT GetHeight();
	UINT GetNumberOfColors();
	RGBQUAD* GetRGB();//获取颜色表指针
	BYTE* GetData();
	BYTE* GetData2();
	DWORD GetDibWidthBytes();
	BITMAPINFO* GetInfo();//获取位图信息结构的指针
	WORD PaletteSize(LPBYTE IpDIB);//位图指针指向的位图调色板的大小
	WORD DIBNumColors(LPBYTE IpDIB);//。。。。。。颜色的数目
	void SaveFile(const CString filename);
	//DWORD GetFilesize();
public:
	void GradetoRGB();
	void RGBtoGrade();
	void LoadFile(CString dibFileName);
};

//#endif