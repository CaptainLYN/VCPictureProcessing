
// MfcPictureProcessingDlg.h : 头文件
//

#pragma once

class CDib;
class CViewImage;
// CMfcPictureProcessingDlg 对话框
class CMfcPictureProcessingDlg : public CDialogEx
{
	
	CMenu m_Menu;
	CString filePath;
	CPoint pt;
#pragma region 这里面都是系统自己生成的，我没动
// 构造
public:
	CMfcPictureProcessingDlg(CWnd* pParent = NULL);	// 标准构造函数
	
// 对话框数据
	enum { IDD = IDD_MFCPICTUREPROCESSING_DIALOG };
	
	

protected:
virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	DECLARE_MESSAGE_MAP()
#pragma endregion
public:
	void GetFilePath(CString file); 

	afx_msg void On32771();//这就是菜单栏的打开文件按钮的函数
	afx_msg void On32772();//向下扫描
	afx_msg void On32773();//向上扫描
	afx_msg void On32774();//向右扫描
	afx_msg void On32775();//向左扫描
	afx_msg void On32776();//水平右移
	afx_msg void On32777();//垂直上移
	afx_msg void On32778();//交叉飞入
	afx_msg void On32779();//中间扩张
	afx_msg void On32780();//清屏
	afx_msg void On32781();//中间收缩
	afx_msg void On32782();//水平栅条
	afx_msg void On32783();//竖直栅条
	afx_msg void On32784();//图像渐显
	afx_msg void On32785();//水平百叶窗
	afx_msg void On32786();//竖直百叶窗
	afx_msg void On32787();//马赛克显示
	afx_msg void OnUpdate32780(CCmdUI *pCmdUI);//清空的消息函数，没有内容
	afx_msg void On32789();//图像平移
	afx_msg void On32790();//水平镜像
	afx_msg void On32791();//垂直镜像
	afx_msg void On32792();//关于软件
	afx_msg void On32793();//图像放大
	
	afx_msg void OnBnClickedButton1();//退出按钮
	afx_msg void On32794();//图像缩小
	afx_msg void On32795();//图像转置
	afx_msg void On32796();//图像旋转
	afx_msg void On32797();//灰度非零取一
	afx_msg void On32798();//灰度固定阈值
	afx_msg void On32799();//保存文件
	afx_msg void On32800();//灰度双阈值
	afx_msg void On32801();//灰度反色转换
	afx_msg void On32802();//灰度窗口变换
	afx_msg void On32803();//折线变换
	afx_msg void On32804();//灰度直方图
	afx_msg void On32805();//灰度分布均衡化
	afx_msg void On32807();//黑白点噪声滤波
	afx_msg void On32808();//消除孤立黑点4连接
	afx_msg void On32809();//消除孤立黑点8连接
	afx_msg void On32810();//3x3均值滤波
	afx_msg void On32811();//超限邻域平均法
	afx_msg void On32812();//选择式掩膜平滑
	afx_msg void On32813();//NxN中值滤波
	afx_msg void On32814();//十字中值滤波
	afx_msg void On32815();//NxN最大值滤波
	afx_msg void On32816();//产生随机噪声
	afx_msg void On32817();//产生椒盐噪声
	afx_msg void On32818();//纵向微分
	afx_msg void On32819();//横向微分
	afx_msg void On32820();//双向微分
	afx_msg void On32821();//门限锐化
	afx_msg void On32822();//固定锐化
	afx_msg void On32823();//二值锐化
	afx_msg void On32824();//Robert算子边缘检测
	afx_msg void On32825();//sobel算子边缘检测
	afx_msg void On32826();//prewitt算子边缘检测
	afx_msg void On32827();//Krisch算子边缘检测
	afx_msg void On32828();//高斯-拉普拉斯算子检测
	afx_msg void On32829();//阈值分割
	afx_msg void On32830();//半阈值分割
	afx_msg void On32831();//迭代阈值分割
	afx_msg void On32832();//轮廓提取
	afx_msg void On32833();//闭合轮廓跟踪
	afx_msg void On32834();//区域增长法
//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
//	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void On32835();//二值图像区域标记
	afx_msg void On32836();//二值图像的周长测量
	afx_msg void On32837();//小区域面积消除
	afx_msg void On32838();//水平投影
	afx_msg void On32839();//垂直投影
	afx_msg void On32840();//水平腐蚀
	afx_msg void On32841();//垂直腐蚀
	afx_msg void On32842();//全方向腐蚀
	afx_msg void On32843();//水平膨胀
	afx_msg void On32844();//垂直膨胀
	afx_msg void On32845();//全方向膨胀
	afx_msg void On32846();//开运算
	afx_msg void On32847();//闭运算
	afx_msg void On32848();//细化
	afx_msg void On32849();//粗化
	afx_msg void On32850();//中轴变换
	afx_msg void On32851();//快速傅里叶变换
	afx_msg void On32852();//离散余弦变换
	afx_msg void On32853();//理想低通滤波器
	afx_msg void On32854();//图像加
	void GetNextFile(CString *file);//用于图像合成中选择第二个图像
	afx_msg void On32855();//图像减
	afx_msg void On32856();//图像与
	afx_msg void On32857();//图像或
	afx_msg void On32858();//图像非
	afx_msg void On32859();//图像或非
	afx_msg void On32860();//图像与非
	afx_msg void On32861();//异或
	afx_msg void On32862();//彩色图像最大值变灰度处理
	afx_msg void On32863();//公式法变灰度
	afx_msg void On32864();//灰度变彩色
	afx_msg void On32865();//亮度调整
	afx_msg void On32866();//对比度调整
	afx_msg void On32867();//亮度的逆反处理
	afx_msg void On32868();//曝光处理
	afx_msg void On32869();//彩色图像的扩散处理
	afx_msg void On32870();//彩色图像马赛克效果
	afx_msg void On32871();//彩色图像邻域平均法平滑
	afx_msg void On32872();//3x3低通滤波
	afx_msg void On32873();//5x5低通滤波
	afx_msg void On32874();//图像的水平增强
	afx_msg void On32875();//图像垂直增强
	afx_msg void On32876();//彩色图像双方向增强
	afx_msg void On32877();//彩色图像梯度锐化
	afx_msg void On32878();//彩色图基本高通
	afx_msg void On32879();//彩色图中等高通滤波
	afx_msg void On32880();//彩色图像过量高通滤波
	afx_msg void On32881();//浮雕处理
	afx_msg void On32882();//彩色图霓虹处理
};
