#pragma once
#include "afx.h"
#include<complex>

class CDib;

class BianHuanYuDib :
	public CObject
{
private:
	CDib *dib;
public:
	BianHuanYuDib(void);
	~BianHuanYuDib(void);
	void GetDib(CDib *dib);
	void QFC(std::complex<double>  *t,std::complex<double> *f,int r);//完全不懂；快速傅里叶变换,t和f分别是指向时域和频域的指针，r是2的幂数
	void FirstQuickFourier();//图像的傅里叶变换（没有对处理后的显示结果进行平移），两次调用快速傅里叶变换QFC()实现二维傅里叶变换
	void LiSan(double *t,double *f,int r);//实现快速离散余弦变换，该函数利用2N点的快速傅里叶变换
	void DIBLiSanYuXian();//改变了原来函数的操作数，调用LiSan（）函数实现图像的离散函数余弦变换
	void PerfectFilterL(int u,int v);//理想低通滤波器，u、v分别是截止频率的x，y分量值，由用户给定
	void TLFilter(int u,int v,int vl);//梯形低通滤波器，u、v分别是截止频率的x、y分量值，由用户指定
};