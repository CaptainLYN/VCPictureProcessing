#pragma once
class HuiDuDib:public CObject
{
protected:
	CDib* dib;
public:
	void Fei0();
	void GetDib(CDib *d);
	void GuDing(int YuZhi);
	void ShuangYu(int low,int high,int mode);
	void FanSe();
	void ChuangKou(BYTE low,BYTE high);
	void ZheXian(BYTE X1,BYTE y1,BYTE X2,BYTE Y2);//优点是根据用户需要，拉伸感兴趣的物体细节，相对抑制不感兴趣的灰度级
	float* ZhiFangTu(bool i);//相比原书，改变了接口,为true返回小数的，为false返回整数的
	void FenBuJunHengHua();//减少像素个数少的灰度级，展宽灰度级个数多的，从而达到清晰图像的目的
	void PiPeiBianHuan(BYTE jishu,int* huidu,float *shuju);//jishu表示要匹配的灰度图有多少级，huidu中依次记录了从小到大每一个灰度值，shuju记录了每一个灰度值的gailv；对原图和目标灰度直方图进行灰度直方图均衡化，然后对于原图的每一个灰度级找到在目标灰度图中的灰度概率最相近的灰度，进行单映射变换，然后对原图进行灰度替换
	int PingJunHuiDu();//返回图像的平均灰度
};