#pragma once
#include<opencv2/opencv.hpp>
using namespace cv;//opencv的命名空间
class QuickDemo
{
public:
	void colorSpace_Demo(Mat &image);//实现BGR转灰度和hsv
	void mat_creat_Demo(Mat &image);//Mat的创建 clone   copyTo   zeros   ones  Scalar  =
	void pixel_visit_demo(Mat &image);//对图像像素的读写操作
	void opreat_demo(Mat &image);//Mat的算术操作 加减乘除及对应的API
	void tracking_bar_demo(Mat &image);//滑动条实现亮度和对比度的调整
	void key_demo(Mat &image);//接收键盘事件
	void color_style_demo(Mat &image);//实现图像色彩变化
	void bitwise_demo(Mat &image);//对Mat实现像素的位操作
	void channels_demo(Mat &image);//图像通道的分离合并
	void inrange_demo(Mat &image);//色彩空间的转换
	void pixel_statistic_demmo(Mat &image);//进行像素值统计
	void drawing_demo(Mat &image);//几何形状绘制
	void randomdrawing_demo(Mat &image);//随机数和随即绘制
	void polylinedrawing_demo(Mat &image);//绘制多边形
	void setMouseCallback_demo(Mat &image);//鼠标操作及相应
	void norm_demo(Mat &image);//像素类型转换及归一化处理
	void resize_demo(Mat &image);//图像放缩及插值
	void flip_demo(Mat &image);//翻转
	void rotate_demo(Mat &image);//旋转
	void video_demo(Mat &image);//视频读取
	void histogram(Mat &image);//获取直方图
	void histogram_2d_demo(Mat &image);//获取二维直方图
	void histogram_eq_demo(Mat &image);//获取直方图的均衡化
	void histogram_compare_demo();//对直方图进行比较
	void histogram_eqRGB_demo(Mat &image);//对彩色图像进行直方图的均衡化
	void blur_demo(Mat &image);//计算卷积
	void gaussian_blur_demo(Mat &image);//计算高斯卷积
	void Bilateralgaussian_blur_demo(Mat &image);//计算双边高斯卷积
	void face_detection_demo();//人脸识别的demo
	void beijing_tihuan_demo();//视频绿布切割背景替换
	void beijing_tihuan_demo1();//加入高斯模糊的绿布抠图替换

	QuickDemo();
	~QuickDemo();

private:
	
	
	
};

