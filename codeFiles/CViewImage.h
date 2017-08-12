#pragma once
class CDib;
class CViewImage:public CView
{
protected:
	CPalette *hPalette;//这两个变量都是指针，为什么不是实体类呢？假如程序一次运行只打开一次文件，类是可以的；多次打开会出现内存错误（大家可以试一下），指针的话，没打开一次都是新建一个类，打开完了即没了，适合用指针
	CDib *dib;
	
public:

	void GetDib(CDib *dib2);//CObject是不能直接作为参数传递的，因为不能被复制，是私有函数

	void virtual OnDraw(CDC *pDC);//CDC类是设备上下文类，用于绘图输出的,实现虚函数
	void OnDraw2(CDC *pC,int x_move,int y_move);//原图像显示位置可以移动的绘图函数
	void OnDraw3(CDC *pDC,LPBYTE temp,int x_move,int y_move);
	void OnDraw4(CDC *pC,int x_move,int y_move,int need_width,int need_height);//可以在原图绘制想要的大小,并没有修改原图的info

    CPalette* CreateBitmapPalette(CDib *pBitmap);
	void OnXiangxia(CDC *pDC);//改成了有参数的，CDC在对话框中获取，在这个函数里面获取有中断问题，没解决为什么
	void OnXiangshang(CDC *pDC);//向上扫描
	void OnXiangyou(CDC *pDC);//向右扫描
	void OnXiangzuo(CDC *pDC);//向左扫描
	void ToShuiPingYouYi(CDC *pDC);//水平右移
	void ToChuiZhiShangYi(CDC *pDC);//垂直上移
	void ToJiaoChaFeiRu(CDC *pDC);//交叉飞入
	void ToSiZhouKuoZhang(CDC *pDC);//四周扩张
	void ToZhongJianShouSuo(CDC *pDC);//中间收缩
	void ToShuiPingShanTiao(CDC *pDC);//水平栅条
	void TOShuZhiShanTiao(CDC *pDC);//竖直栅条
	void ToTuXiangJianXian(CDC *pDC);//图像渐显
	void ToShuiPingBaiYeChuang(CDC* pDC);//水平百叶窗
	void ToShuZhiBaiYeChuang(CDC* pDC);//垂直百叶窗
	void ToMaSaiKeXianShi(CDC *pDC);//马赛克显示

};//这边少一个分号就多了20几个错误，因为include后面没有分号