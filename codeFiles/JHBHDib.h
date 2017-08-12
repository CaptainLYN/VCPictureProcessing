#pragma once
class CDib;
class JHBHDib:public CObject
{
protected:
	CDib *dib;
public:
	void GetDib(CDib* cdib);
	JHBHDib();
	~JHBHDib();
	void PingYi(int m_Xmove,int m_Ymove);
	void JingXiang(bool fangshi);

	//内存一定要在主程序申请，否则程序结束就收回了
	LPBYTE FangDa(LPBYTE temp,int xzoom,int yzoom,long width,long height,int newwidth,int newheight);//横和纵的放大倍数,这里降低一下要求，是int
	void SuoXiao(float xzoom,float yzoom);
	LPBYTE ZhuanZhi();
	LPBYTE XuanZhuan(double RotateAngle);
	double RADIAN(double RotateAngle);

};