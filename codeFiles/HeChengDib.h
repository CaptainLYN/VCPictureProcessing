#pragma once
#include "afx.h"
class CDib;
class HeChengDib :
	public CObject
{
private:
	CDib *dib;
public:
	HeChengDib(void);
	~HeChengDib(void);
	void GetDib(CDib *dib);
	void Add(LPBYTE p_dataBK);//图像背景;和原函数参数改变了;两幅图像大小必须一致(虽然不一样也能用)
	void Sub(LPBYTE p_dataBK);//减运算可以用来识别物体在特定区域的运动情况
	void Yu(LPBYTE p_dataBK);//与运算
	void Huo(LPBYTE p_dataBK);//或运算
	void Fei();//非运算
	void HuoFei(LPBYTE p_dataBK);//或非运算，两像素点同时为0置1（255），否则置0
	void YuFei(LPBYTE p_dataBK);//与非运算，两像素点同时为1置0，其他为0
	void YiHuo(LPBYTE p_dataBK);//异或运算，两像素点相同置0，否则置1（255）
};

