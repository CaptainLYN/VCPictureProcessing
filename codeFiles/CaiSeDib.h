#pragma once
#include "afx.h"
class CDib;
class CaiSeDib :
	public CObject
{
private:
	CDib *dib;
public:
	CaiSeDib(void);//亮度（光的能量越大，亮度越大）、饱和度（颜色中白色的比例越大饱和度越小）、色调（决定颜色的本质）
	~CaiSeDib(void);
	void GetDib(CDib *dib);
	void MaxGray();//灰度化，用R,G,B分量的最大值来作灰度
	void GongShiGray();//灰度化，用那个公式
	void PaintColor(int m_red,int m_green,int m_blue);//将灰度图像变为彩色图像；对图像使用阈值法进行着色处理
	void LightAlter(int m_light);//调整图像各颜色值的亮度，输入0~100百分比
	void ContrastAlter(int m_increment);//改变对比度，输入值在-127~128，大于零增强对比度，小于零减少对比度;利用阈值法调整对比度；数值太大的话连颜色都改了
	void LightReverse();//亮度取反
	void Exposal();//曝光处理，对于每一个颜色分量，小于128都进行取反；会损失可以看到的明快的颜色和色调
	void Spread();//扩散处理，从当前像素周围5x5区域内随机选择一个像素作为当前像素值；书上说有油画的感觉
	void Mosaic();//使图像产生马赛克效果,对周围5x5矩阵，各颜色分开求和去平均值，赋值给该颜色在矩阵中的所有量
	void Smoothness();//平滑处理；每个颜色分量都是周围3x3矩阵的颜色分量的平均值
	void Lowlvbo3();//3x3低通滤波
	void Lowlvbo5();//5x5低通滤波
	void ShuiPingGrow();//锐化；图像的水平增强实际上也是一种高通滤波；h[1][3]={-1  2  -1},他的理论和写的代码是不一样的，而且感觉书上的水平和垂直写反了，我这里把它反过来
	void ChuiZhiGrow();//锐化；垂直增强
	void ShuangXiangGrow();//锐化；图像的双向增强
	void Sharp();//梯度锐化;当前像素值=（当前像素值-（j-1,i-1)）/4+当前像素值
	void Gaotonglvbo(int m_Gaotong);//三个矩阵分别对应基本高通、中等高通和过量高通；高通滤波就是对图像的低频分量进行抑制，让图像的高频分量无损耗或者低损耗的通过滤波器
	void FuDiao();//感觉跟横向微分差不多，分量值=分量值-左边+128;让边界变化突出，内部颜色变浅，从而有纵深感，只有颜色变化区才会出现彩色
	void NiHong();//是图像边缘出现霓虹处理效果，内部是黑色的；当前点只与横向和竖向的点有关，所以同一条线，不管是直线斜线弯线，才会有同样的颜色，一条线上的点距离近的点周围的点是差不多的
};

