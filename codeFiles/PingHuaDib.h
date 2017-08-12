#pragma once
class CDib;
class PingHuaDib:public CObject
{
private:
	CDib* dib;
	/*线性平滑就是对每一个像素值用它的邻域值代替，不论是3x3或是NxN都相当于图像经过了一个二维的低通滤波器，虽然降低了噪声，
	但是也模糊了图像的边缘和细节，这是这类滤波存在的通病;
	非线性变化，就是取一个阈值，像素点和邻域平均值的差值大于阈值时才用均值替换，小于时保持自己的灰度值。
	自适应平滑，就是根据具体的均值和方差的情况选择不一样的平滑方式。噪声和图像之间有些是相关的，有些是不相关的，噪声和噪声之间有些也是相关的。
	目标就是尽量不模糊边缘轮廓，如选择式掩模平滑。
	*/
public:
	void GetDib(CDib* sdib);
	void HeiBaiZaoSheng();//二值图像的黑白点噪声消除，消除孤立的黑像素点，算周围8像素值的平均值，如果和当前点差值在127.5以上，就进行黑白翻转，不到就不变
	void ErZhiHua(int yuzhi);//二值化,但是每个像素还是8位，黑9白255
	void GuLiHei(int connec);//消除孤立的黑像素点
	void ThreeThree();//3x3均值滤波，如果是灰度图，效果就像蒙了一层雾；模板内的数值和是1，是为了保持平滑处理后的图像的平均值不变；代价是图形模糊，模板面积越大噪声减少越显著
	void ChaoXian(int yuzhi);//超限邻域平均法；设置一个阈值，当前点的值和周围8邻域的均值差值大于阈值就替换，否则保留
	//有一个用户输入窗口值的我没写，重复代码
	void JuBuPingJun();//选择式掩模平滑,水彩画的效果；5x5窗口，对9个模板选择方差最小的进行均值进行替换
	//中值滤波特别试用于胡椒粉式或脉冲式的干扰图像
    void nnZhongZhi(int n);//NxN中值滤波，n为窗口大小 ；非线性的，无条件用中值代替
	void shizi(int n);//十字滤波
	void nnZuiDa(int n);//NxN最大值滤波
	void SuiJiZaoSheng();//产生随机噪声,产生的多且密
	void JiaoYanZaoSheng();//产生的较疏
};