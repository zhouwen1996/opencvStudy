#include "QuickDemo.h"
#include <opencv2/dnn.hpp>
#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>
//实现BGR转灰度和hsv
void QuickDemo::colorSpace_Demo(Mat &image)
{
	Mat gray;
	Mat hsv;
	cvtColor(image, gray, COLOR_BGR2GRAY);//第三个参数可以根据你的src和dst自己选择
	cvtColor(image, hsv, COLOR_BGR2HSV);
	imshow("灰度", gray);
	imshow("HSV", hsv);
	imwrite("hsv.png",hsv);//有第三个参数 但只关心前两个
	imwrite("gray.png", gray);
	return;
}
//Mat的创建 clone   copyTo   zeros   ones  Scalar  =
void QuickDemo::mat_creat_Demo(Mat &image)
{
	Mat mClone;
	Mat mCopy;
	mClone = image.clone();//克隆
	image.copyTo(mCopy);//复制

	//创建空白mat  CV_8UC1表示8位 无符号类型 channel通道为1
	Mat mEmpty = Mat::zeros(Size(8,8),CV_8UC1);//创建大小为8x8的单通道的空mat
	Mat mOnes = Mat::ones(Size(8, 8), CV_8UC3);//注意使用ones初始化为1的时候是只把每个像素的第一个通道初始化为1，其他还是0
	std::cout << "ones ；Size(8,8)  CV_8UC3:" << mOnes << std::endl;
	std::cout << "Size(8,8)  CV_8UC1:" <<  mEmpty << std::endl;
	std::cout << "width=" << mEmpty.cols << ",height=" << mEmpty.rows << ",channele=" << mEmpty.channels() << std::endl;
	std::cout << "====================" << std::endl;
	Mat mEmptyC3 = Mat::zeros(Size(8, 8), CV_8UC3);//创建大小为8x8的3通道的空mat
	std::cout << "Size(8,8)  CV_8UC3:" << mEmptyC3 << std::endl;
	std::cout << "width=" << mEmptyC3.cols << ",height=" << mEmptyC3.rows << ",channele=" << mEmptyC3.channels() << std::endl;

	//赋值操作
	mEmptyC3 = 127;//这种赋值方法也同样只是会对每个像素的第一个通道赋值为127其他的不变
	std::cout << "mEmptyC3 = 127;:" << mEmptyC3 << std::endl;

	//创建底色画布的
	mEmptyC3 = Scalar(127, 127, 127);//如果想要操作每个通道则要使用Scalar，
	std::cout << "mEmptyC3 = Scalar(127, 127, 127);:" << mEmptyC3 << std::endl;

	imshow("创建窗口", mEmptyC3);//注意imshow支持8位或浮点数类型 有限制的

	//验证赋值操作 其实数据区复制，只是指针赋值，因此=操作会改变原来mat
	//但是clone和copyto是产生新的数据区，不会影响原来的。
	Mat mEqualOpr = mEmptyC3;
	mEqualOpr = Scalar(0, 255, 255);
	imshow("创建窗口1", mEmptyC3);

	return;
}
//对图像像素的读写操作
void QuickDemo::pixel_visit_demo(Mat &image)
{
	int w = image.cols;
	int h = image.rows;
	int channel = image.channels();
	for (int row = 0; row < h; row++)
	{
		uchar* current_row = image.ptr<uchar>(row);
		for (int cols = 0; cols < w; cols++)
		{
			if (channel == 1)//单通道 灰度图
			{
				*current_row++ = 255 - *current_row;//保证数据在255之间，数据不越出。
			}
			else if (channel == 3)//三通道
			{
				//每次访问一个字节，并且进行++移动
				*(current_row++) = 255 - *current_row;
				*(current_row++) = 255 - *current_row;
				*(current_row++) = 255 - *current_row;
			}
		}
	}
	//for (int row = 0; row < h; row++)
	//{
	//	for (int  cols = 0; cols < w; cols++)
	//	{
	//		if (channel == 1)//单通道 灰度图
	//		{
	//			int p = image.at<uchar>(row, cols);//读操作 uchar无符号字节类型 转换为int
	//			image.at<uchar>(row, cols) = 255 - p;//保证数据在255之间，数据不越出。
	//		}
	//		else if (channel == 3)//三通道
	//		{
	//			Vec3b bgr = image.at<Vec3b>(row, cols);//有Vec3b这样的数据类型 一次读取三个值，重定义Vec<uchar, 3>
	//			//写
	//			image.at<Vec3b>(row, cols)[0] = 255 - bgr[0];
	//			image.at<Vec3b>(row, cols)[1] = 255 - bgr[1];
	//			image.at<Vec3b>(row, cols)[2] = 255 - bgr[2];
	//		}
	//	}
	//}
	imshow("像素读写显示",image);
}
//Mat的算术操作 加减乘除及对应的API
void QuickDemo::opreat_demo(Mat &image)
{
	Mat dst;
	////Scalar表示标量
	dst = image + Scalar(50, 50, 50);//也可以使用opencv自带api；add()方法
	imshow("加法操作", dst);
	dst = image - Scalar(50, 50, 50);
	imshow("减法操作", dst);
	dst = image / Scalar(4, 4, 4);//也可以使用divide()方法
	imshow("除法操作", dst);
	/*dst = image * Scalar(2, 2, 2);直接乘法会存在数据溢出报错，opencv中提供了专门的乘法函数
	imshow("乘法法操作", dst);*/
	//opencv提供的乘法函数 他会将超出范围的数据自动截取 
	//使用saturate_cast<uchar>函数 小于0则是0 大于255则是255

	//注意需创建大小与image相同的mat进行乘法  可以这样 直接Scalar也可以
	//Mat m = Mat::zeros(image.size(), image.type());
	//m = Scalar(2, 2, 2);
	multiply(image, Scalar(2, 2, 2), dst);
	imshow("乘法操作", dst);

	//自定义加法操作
	Mat m = Mat::zeros(image.size(), image.type());
	dst = Mat::zeros(image.size(), image.type());
	m = Scalar(50, 50, 50);
	int w = image.cols;
	int h = image.rows;
	int channel = image.channels();
	for (int row = 0; row < h; row++)
	{
		uchar* current_row = image.ptr<uchar>(row);
		uchar* current_m = m.ptr<uchar>(row);
		uchar* current_dst = dst.ptr<uchar>(row);
		for (int cols = 0; cols < w; cols++)
		{
			//每次访问一个字节，并且进行++移动
			//关键 saturate_cast  保证数据类型在范围内
			*(current_dst++) = saturate_cast<uchar>(*current_row++ + *current_m++);
			*(current_dst++) = saturate_cast<uchar>(*current_row++ + *current_m++);
			*(current_dst++) = saturate_cast<uchar>(*current_row++ + *current_m++);
		}
	}
	imshow("自定义加法操作", dst);

	return;
}

//这个int b就是亮度调整传过来的值
//void *userdata  任何类型的指针 只是要类型转换
static void on_track(int b, void *userdata)
{
	Mat image = *((Mat *)userdata);
	Mat mTemp = Mat::zeros(image.size(), image.type());
	Mat dst = Mat::zeros(image.size(), image.type());
	addWeighted(image, 1.0, mTemp, 0, b, dst);//图像混合 根据各种权重
	imshow("亮度调整", dst);
}
static void on_constrast(int b, void *userdata)
{
	Mat image = *((Mat *)userdata);
	Mat mTemp = Mat::zeros(image.size(), image.type());
	Mat dst = Mat::zeros(image.size(), image.type());
	double constrat = b / 100.0;
	addWeighted(image, constrat, mTemp, 0.0, 0, dst);
	imshow("亮度调整", dst);
}
//滑动条实现亮度和对比度的调整
void QuickDemo::tracking_bar_demo(Mat &image)
{
	int lightness = 50;//亮度值
	namedWindow("亮度调整", WINDOW_AUTOSIZE);
	int max_value = 100;
	int constract_value = 100;
	//on_track  回调函数
	createTrackbar("Value Bar:", "亮度调整", &lightness, max_value, on_track, (void *)(&image));
	createTrackbar("constrat Bar:", "亮度调整", &constract_value, 200, on_constrast, (void *)(&image));
	//首先要调用一次，否则刚开始是没有图像的，要点击才有，第二个参数没有就传0
	on_track(50, &image);
	return;
}
//接收键盘事件
void QuickDemo::key_demo(Mat &image)
{
	Mat dst = Mat::zeros(image.size(), image.type());
	while (true)
	{
		//永远要记得一点在做视频分析的时候waitKey一定要传入1
		int c = waitKey(100);//Waits for a pressed key. 等待100ms
		//std::cout << c << std::endl;  暂时先测试按下什么按键在opencv中对应的值
		if (c == 27)//esc 退出27
		{
			break;
		}
		else if (c == 49)//点击图片按数字1进行灰度转换
		{
			std::cout << "you enter key #1" << std::endl;
			cvtColor(image, dst, COLOR_BGR2GRAY);
		}
		else if (c == 50)//点击图片按数字2进行hsv转换
		{
			std::cout << "you enter key #2" << std::endl;
			cvtColor(image, dst, COLOR_BGR2HSV);
		}
		else if (c == 51)//点击图片按数字3进行亮度增加转换
		{
			std::cout << "you enter key #3" << std::endl;
			add(image, Scalar(50, 50, 50), dst);
		}
		imshow("显示操作结果图片", dst);
	}

	return;
}
//色彩表 //实现图像色彩变化
void QuickDemo::color_style_demo(Mat &image)
{
	//enum ColormapTypes  支持的20种色彩空间
	int colorMap[] = 
	{
		COLORMAP_AUTUMN,
		COLORMAP_BONE,
		COLORMAP_JET,
		COLORMAP_WINTER,
		COLORMAP_RAINBOW,
		COLORMAP_OCEAN,
		COLORMAP_SUMMER,
		COLORMAP_SPRING,
		COLORMAP_COOL,
		COLORMAP_HSV ,
		COLORMAP_PINK ,
		COLORMAP_HOT,
		COLORMAP_PARULA,
		COLORMAP_MAGMA,
		COLORMAP_INFERNO,
		COLORMAP_PLASMA,
		COLORMAP_VIRIDIS,
		COLORMAP_CIVIDIS,
		COLORMAP_TWILIGHT,
		COLORMAP_TWILIGHT_SHIFTED
	};
	Mat dst;
	int index = 0;
	while (true)
	{
		int c = waitKey(2000);//Waits for a pressed key. 等待100ms
		if (c == 27)//esc 退出27
		{
			break;
		}
		applyColorMap(image, dst, colorMap[index%19]);
		index++;
		imshow("颜色风格", dst);
	}

}
//对Mat实现像素的位操作
void QuickDemo::bitwise_demo(Mat &image)
{
	Mat m1 = Mat::zeros(Size(256, 256), CV_8UC3);
	Mat m2 = Mat::zeros(Size(256, 256), CV_8UC3);
	Mat m3 = Mat::zeros(Size(256, 256), CV_8UC3);
	rectangle(m1,Rect(100, 100, 80, 80), Scalar(255, 255, 0), -1, LINE_8, 0);//-1表示填充矩形，LINE_8表示利用周围8个像素
	rectangle(m2, Rect(150, 150, 80, 80), Scalar(0, 255, 255), -1, LINE_8, 0);
	rectangle(m3, Rect(0, 0, 80, 80), Scalar(255, 0, 255),5, LINE_8, 0);//绘制 相当于描边
	imshow("m1", m1);
	imshow("m2", m2);
	imshow("m3", m3);

	Mat dst;
	bitwise_and(m1, m2, dst);//相当于交集
	imshow("像素位操作与", dst);
	bitwise_or(m1, m2, dst);//全集  
	imshow("像素位操作或", dst);
	bitwise_not(image, dst);
	//dst = ~image;//也是可以的
	imshow("像素位操作非", dst);
	bitwise_xor(m1, m2, dst);
	imshow("像素位操作异或", dst);
	return;
}
//图像通道的分离合并
void QuickDemo::channels_demo(Mat &image)
{
	//图像分离split函数
	std::vector<Mat> mv;
	//opencv顺序是BGR的
	split(image, mv); //分离成三个通道对应三种颜色
	imshow("蓝色", mv[0]);
	imshow("绿色", mv[1]);
	imshow("红色", mv[2]);

	//合并通道到目标mat
	Mat dst;
	mv[1] = 0;//只保留蓝色
	mv[2] = 0;
	merge(mv, dst);
	imshow("只显示蓝色", dst);

	//混合交互通道
	int from_to[] = {0,2, 1,1, 2,0};//通道交互从哪里到哪里  第一张0通道到第二张2通道
	mixChannels(&image, 1, &dst, 1, from_to, 3);//支持多张图片  1表示多少张图片  3表示有几对通道交换数据
	imshow("通道混合", dst);
}

//色彩空间的转换
void QuickDemo::inrange_demo(Mat &image)
{
	Mat hsv;
	cvtColor(image, hsv, COLOR_BGR2HSV);
	Mat mask;
	/*
	inRange可实现二值化功能,
	主要是将在两个阈值内的像素值设置为白色（255），而不在阈值区间内的像素值设置为黑色（0），
	该功能类似于之间所讲的双阈值化操作。
	*/
	inRange(hsv, Scalar(35, 43, 46), Scalar(77, 255, 255), mask);//输入hsv图像、 根据绿色作为分界则传入hsv绿色的hsv最大最下值
	imshow("inRange mask", mask);//只有黑白  把绿色都变成1白色 其他变成0黑色

	Mat reaback = Mat::zeros(image.size(), image.type());
	reaback = Scalar(40, 40, 200);//红底
	bitwise_not(mask, mask);//取反 黑变白 白变黑   就是相当于把绿色部分变成0黑色、人部分变成1白色
	imshow("bitwise_not mask", mask);
	/*
	//mask的意思就是image在copy的时候只有像素不为0的点才会copy到reaback上去
	相当于只人部分变成1白色部分从image上叠加上去，其他不变
	（就是把image人所在区域拷贝到reaback上来）
	*/
	image.copyTo(reaback, mask);
	imshow("roi区域提取", reaback);
}
//进行像素值统计
void QuickDemo::pixel_statistic_demmo(Mat &image)
{
	double minv, maxv;//注意是double类型
	Point minLoc, maxLoc;//最大最小的地址
	std::vector<Mat> mv;
	split(image, mv);
	for (int i = 0; i < mv.size(); i++)
	{
		minMaxLoc(mv[i], &minv, &maxv, &minLoc, &maxLoc, Mat());//传入参数必须是单通道的、得先split
		std::cout << "minvalue:" << minv << "  maxvalue:" << maxv << std::endl;
	}
	
	Mat mean, stddev;
	meanStdDev(image,mean,stddev);//第四个参数mask就是iro不规则区域计算
	std::cout << "mean:" << mean << std::endl;
	std::cout << "mean[0]:" << mean.at<double>(0) << std::endl;
	//方差小就是图像的对比度差异度低、有效信息低
	//因此在图像分析当中，可以根据方差值小表示周围差异性小 从而是可以过滤掉一些东西的
	std::cout << "stddev:" << stddev << std::endl;
}

//几何形状绘制
void QuickDemo::drawing_demo(Mat &image)
{
	//坐标的原点是从左上角为0 0
	//绘制矩形是可以有类型定义的
	Rect rect;
	rect.x = 150;
	rect.y = 20;
	rect.width = 70;
	rect.height = 100;
	
	Mat bg = Mat::zeros(image.size(), image.type());
	//rectangle(bg, rect, Scalar(0, 0, 255), 5, 0);
	rectangle(bg, rect, Scalar(0, 0, 255), -1, 0);//thickness参数改成小于0则表示填充
	circle(bg, Point(200, 200), 50, Scalar(255, 0, 0), -1, 0);//画圆
	line(bg, Point(100, 100), Point(255, 255), Scalar(0,0,0),8, 8, 0);//lineType图像锯齿问题
	RotatedRect rrt;//椭圆
	rrt.center = Point(300,300);
	rrt.size = Size(50,100);
	rrt.angle = 0;
	ellipse(bg, rrt, Scalar(0, 255, 255), 2, 8);
	Mat dst;
	addWeighted(image, 0.7, bg, 0.3, 0, dst);//image占比0.7，bg占比0.3 叠加

	imshow("绘制几何", dst);
}
//随机数和随即绘制
void QuickDemo::randomdrawing_demo(Mat &image)
{
	Mat canvas = Mat::zeros(Size(500, 500), CV_8UC3);
	int w = canvas.cols;
	int h = canvas.rows;
	RNG rng(12345);//产生随机数 传入种子 一般传入时间
	while (true)
	{
		int c = waitKey(10);
		if (c == 27)
		{
			break;
		}
		int x1 = rng.uniform(0, w);//在0 - w范围内产生一个随机数
		int y1 = rng.uniform(0, h);
		int x2 = rng.uniform(0, w);//在0 - w范围内产生一个随机数
		int y2 = rng.uniform(0, h);
		int b = rng.uniform(0, 255);
		int g = rng.uniform(0, 255);
		int r = rng.uniform(0, 255);
		//canvas = Scalar(0, 0, 0);每次画布更新 达到每次图像只有一条线
		line(canvas, Point(x1, y1), Point(x2, y2), Scalar(b, g, r), 1, LINE_AA, 0);//lineType图像锯齿问题
		imshow("随机绘制", canvas);
	}
	return;
}
//绘制多边形
void QuickDemo::polylinedrawing_demo(Mat &image)
{
	Mat canvas = Mat::zeros(Size(500, 500), CV_8UC3);
	Point p1(100, 100);
	Point p2(350, 100);

	Point p3(450, 280);
	Point p4(320, 450);
	Point p5(80, 400);
	std::vector<Point> vc_pts;
	vc_pts.push_back(p1);
	vc_pts.push_back(p2);
	vc_pts.push_back(p3);
	vc_pts.push_back(p4);
	vc_pts.push_back(p5);
	//要实现边框加填充就要注意fillPoly、polylines的顺序
	fillPoly(canvas, vc_pts, Scalar(255, 0, 255), 8, 0);//只能填充
	polylines(canvas, vc_pts, true, Scalar(0, 0, 255), 1, LINE_AA, 0);//这里的thickness只能传大于0 不能填充只能绘制
	imshow("多边形绘制", canvas);

	//显示多个多边形函数  绘制填充都可以选择
	std::vector<std::vector<Point>> contous;
	contous.push_back(vc_pts);
	//contourIdx索引显示第几个，-1表示都显示出来  
	//thickness  可以传入-1表示填充
	drawContours(canvas, contous, -1, Scalar(255, 0, 0), -1);
	imshow("多边形绘制1", canvas);

	return;
}
//鼠标操作及相应
Point sp(-1, -1);
Point ep(-1, -1);
Mat tempImage;
static void on_draw(int event, int x, int y, int flags, void *usrdata)
{
	Mat image = *((Mat *)usrdata);
	if (event == EVENT_LBUTTONDOWN)//鼠标左键按下事件
	{
		sp.x = x;
		sp.y = y;
		std::cout << "start Point: " << sp << std::endl;
	}
	else if (event == EVENT_LBUTTONUP)//左键松开
	{
		ep.x = x;
		ep.y = y;
		int dx = ep.x - sp.x;
		int dy = ep.y - sp.y;
		if (dx > 0 && dy > 0)
		{
			Rect box(sp.x, sp.y, dx, dy);
			//注意顺序 不然提取区域会有红色矩形框
			tempImage.copyTo(image);
			imshow("ROI区域", image(box));//截取鼠标款选的区域
			rectangle(image, box, Scalar(0, 0, 255), 2);
			imshow("鼠标绘制", image);

			//给下次绘制初始化
			sp.x = -1;
			sp.y = -1;
		}
		std::cout << "end Point: " << ep << std::endl;
	}
	else if (event == EVENT_MOUSEMOVE)
	{
		if (sp.x >0 && sp.y > 0)
		{
			ep.x = x;
			ep.y = y;
			int dx = ep.x - sp.x;
			int dy = ep.y - sp.y;
			if (dx > 0 && dy > 0)
			{
				Rect box(sp.x, sp.y, dx, dy);
				tempImage.copyTo(image);//保证每次 绘制image都是最初的
				rectangle(image, box, Scalar(0, 0, 255), 2);
				imshow("鼠标绘制", image);
			}
		}
		
	}
	return;
}
void QuickDemo::setMouseCallback_demo(Mat &image)
{
	namedWindow("鼠标绘制", WINDOW_AUTOSIZE);
	setMouseCallback("鼠标绘制", on_draw, (void *)&image);
	tempImage = image.clone();
	imshow("鼠标绘制", image);
}

//像素类型转换及归一化处理
void QuickDemo::norm_demo(Mat &image)
{
	Mat dst;
	std::cout << image.type() << std::endl;
	image.convertTo(image, CV_32F);//转化为32位的浮点数
	std::cout << image.type() << std::endl;//type()输出的值是opencv重定义的枚举类型值
	normalize(image, dst, 1.0, 0, NORM_MINMAX);
	std::cout << dst.type() << std::endl;
	imshow("图像数据归一化", dst);
}

//图像放缩及插值
void QuickDemo::resize_demo(Mat &image)
{
	Mat zoomin;
	Mat zoomax;
	int w = image.cols;
	int h = image.rows;
	resize(image, zoomin, Size(w/2, h/2), 0, 0, INTER_LINEAR);
	imshow("zoomin", zoomin);
	resize(image, zoomax, Size(w * 1.5, h * 1.5), 0, 0, INTER_LINEAR);
	imshow("zoomax", zoomax);
}
//翻转
void QuickDemo::flip_demo(Mat &image)
{
	Mat dst;
	flip(image, dst, 0);//上下翻转
	imshow("上下翻转", dst);
	flip(image, dst, 1);//大于0 左右翻转
	imshow("左右翻转", dst);
	flip(image, dst, -1);//小于0  上下左右都翻转 就是180度旋转
	imshow("180度旋转", dst);
}
//旋转
void QuickDemo::rotate_demo(Mat &image)
{
	Mat dst, M;
	int w = image.cols;
	int h = image.rows;
	M = getRotationMatrix2D(Point2f(w/2, h/2), 45, 1.0);//得到旋转45度的矩阵
	//计算旋转后的图片大小  这个是得到旋转Mat可以知道的对应的cos、sin
	double cos = abs(M.at<double>(0, 0));
	double sin = abs(M.at<double>(0, 1));
	//计算旋转后的新宽高  根据几何知识 
	int nh = cos*w + sin*h;
	int nw = sin*w + cos*h;
	//计算偏移量 修改中心的偏移量  因为warpAffine需要传入的mat的中心坐标
	M.at<double>(0, 2) += (nw/2 - w/2);
	M.at<double>(1, 2) += (nh / 2 - h / 2);
	warpAffine(image, dst, M, Size(nw, nh), INTER_LINEAR, 0, Scalar(255, 0, 0));
	imshow("旋转演示", dst);//没有遮挡的
}
//视频读取
void QuickDemo::video_demo(Mat &image)
{
	//VideoCapture captureCamear(0);//传入0表示读取摄像头 还可以传入视频文件的全路径字符串
	/*
	//如果读取视频文件的帧宽高失败则需要
	将opencv安装目录D:\opencv\build\x64\vc14\bin中的opencv_videoio_ffmpeg440_64.dll复制
	到生成项目的.exe所在的文件（Debug/Release）中。
	（因为我用OpenCV版本是4.4，所以ffmpeg440）
	*/
	VideoCapture captureCamear("C:/Users/20531/Desktop/1.mp4");
	//get视频属性 注意也是可以set设置的 但是注意如果是摄像头的话他硬件是否支持set的参数
	int frame_width = captureCamear.get(CAP_PROP_FRAME_WIDTH);
	int frame_height = captureCamear.get(CAP_PROP_FRAME_HEIGHT);
	int frame_counts = captureCamear.get(CAP_PROP_FRAME_COUNT);
	int fps = captureCamear.get(CAP_PROP_FPS);
	std::cout << "frame_width = " << frame_width << std::endl;
	std::cout << "frame_height = " << frame_height << std::endl;
	std::cout << "frame_counts = " << frame_counts << std::endl;
	std::cout << "fps = " << fps << std::endl;

	//CAP_PROP_FOURCC  获取原来的编码类型   注意size的大小不能变
	VideoWriter writer("D:/test.mp4", captureCamear.get(CAP_PROP_FOURCC), fps, Size(frame_width, frame_height), true);

	Mat frameCamear;
	Mat frameVedio;
	while (true)
	{
		captureCamear.read(frameCamear);//读取视频 每一帧 从而操作视频就是操作图像了
		//captureVedio.read(frameVedio);
		flip(frameCamear, frameCamear, 1);//左右翻转一下 与实际保持一致
		writer.write(frameCamear);//写入文件
		if (frameCamear.empty())
		{
			break;
		}
		imshow("frame", frameCamear);
		int c = waitKey(10);
		if (c == 27)
			break;
	}
	//captureVedio.release();
	captureCamear.release();//摄像头资源需要释放
	writer.release();//视频写入变量也需要释放资源
}
//获取直方图
void QuickDemo::histogram(Mat &image)
{
	//分割通道
	std::vector<Mat> bgr_plane;
	split(image, bgr_plane);
	//定义参数变量
	const int channels[1] = { 0 };
	const int bins[1] = { 256 };//直方图的取值个数
	float hranges[2] = { 0, 255 };//直方图的取值范围
	const float* ranges[1] = {hranges};//因为接口可以支持多维的 多张图像
	Mat b_hist;
	Mat g_hist;
	Mat r_hist;

	//计算直方图
	calcHist(&bgr_plane[0], 1, 0, Mat(), b_hist, 1, bins, ranges);
	calcHist(&bgr_plane[1], 1, 0, Mat(), g_hist, 1, bins, ranges);
	calcHist(&bgr_plane[2], 1, 0, Mat(), r_hist, 1, bins, ranges);

	//显示直方图
	int hist_w = 512;
	int hist_h = 400;
	int bin_w = cvRound((double)hist_w/bins[0]);//每个bin是256个，总宽度除以它得到每个灰度值在图像中占几个像素点，最终是要画图的
	Mat hisImage = Mat::zeros(hist_h, hist_w, CV_8UC3);//绘制直方图的底布

	//归一化处理 因为三个通道出现的相同灰度值次数差值太大了因此需要归一化到一段范围内 (底布高度范围这么大)来显示在一张图片上
	normalize(b_hist, b_hist, 0, hisImage.rows, NORM_MINMAX, -1, Mat());
	normalize(g_hist, g_hist, 0, hisImage.rows, NORM_MINMAX, -1, Mat());
	normalize(r_hist, r_hist, 0, hisImage.rows, NORM_MINMAX, -1, Mat());
	//绘制直方图曲线
	for (int i = 1; i < bins[0]; i++)
	{
		//点的坐标都是基于屏幕坐标的 因此要做转换 hist_h -cvRound(b_hist.at<float>(i-1)))
		line(hisImage, Point(bin_w*(i-1), hist_h -cvRound(b_hist.at<float>(i-1))),
		Point(bin_w*(i), hist_h-cvRound(b_hist.at<float>(i))), Scalar(255,0,0),2,8,0);
		line(hisImage, Point(bin_w*(i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(g_hist.at<float>(i))), Scalar(0, 255, 0), 2, 8, 0);
		line(hisImage, Point(bin_w*(i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(r_hist.at<float>(i))), Scalar(0, 0, 255), 2, 8, 0);
	}
	//显示直方图
	namedWindow("Histogram Deemo", WINDOW_AUTOSIZE);
	imshow("Histogram Deemo", hisImage);
}
//获取二维直方图
void QuickDemo::histogram_2d_demo(Mat &image)
{
	//2D直方图
	Mat hsv, hsv_hist;
	cvtColor(image, hsv, COLOR_BGR2HSV);
	int hbins = 30;//h的灰度只是0-179，一共180个灰度值，30个灰度值为一个单位统计在该范围内的像素频率
	int sbins = 32;//s的灰度值实时0-255
	int hist_bins[] = {hbins, sbins};//2d将两组bins设置进去
	float h_range[] = {0, 180};//灰度值的取值范围
	float s_range[] = { 0, 256 };
	const float* hs_range[] = {h_range, s_range};
	int hs_channels[] = { 0, 1 };
	//hsv 只有一张图像  第0个和第一个通道、mask就是与之前的一样 只对非0的做处理  产生的mat  2维的 第1、2个通道多少个bins  第1、2个通道多少个取值范围
	//这个就是在得出每个灰度值对应的像素点的个数
	calcHist(&hsv, 1, hs_channels, Mat(), hsv_hist, 2, hist_bins, hs_range, true, false);
	//2维的一图图像里面 则首先要进行归一化处理
	double maxVal = 0;
	minMaxLoc(hsv_hist, 0, &maxVal, 0, 0);//最大值
	int scale = 10;
	Mat hist2d_image = Mat::zeros(sbins*scale, hbins*scale, CV_8UC3);//创建空白图像 将数据往上面填入即可
	for (int h = 0; h < hbins; h++)
	{
		for (int s = 0; s < sbins; s++)
		{
			float binVal = hsv_hist.at<float>(h, s);
			int intensity = cvRound(binVal * 255 / maxVal);//取整
			rectangle(hist2d_image, Point(h*scale, s*scale),
				Point((h+1)*scale -1, (s+1)*scale -1),
				Scalar::all(intensity), -1);
		}
	}
	applyColorMap(hist2d_image, hist2d_image, COLORMAP_JET);//变成色彩图
	imshow("H-S Histogram", hist2d_image);
}
//获取直方图的均衡化
void QuickDemo::histogram_eq_demo(Mat &image)
{
	namedWindow("灰度图像", WINDOW_FREERATIO);
	namedWindow("直方图均衡化", WINDOW_FREERATIO);//图片太大了
	Mat gray;
	cvtColor(image, gray, COLOR_BGR2GRAY);//灰度图像
	imshow("灰度图像", gray);
	Mat dst;
	equalizeHist(gray, dst);
	imshow("直方图均衡化", dst);
}


//对彩色图像进行直方图的均衡化
void QuickDemo::histogram_eqRGB_demo(Mat &image)
{
	namedWindow("RGB图像", WINDOW_FREERATIO);
	namedWindow("直方图均衡化", WINDOW_FREERATIO);//图片太大了
	Mat ycrcb;
	cvtColor(image, ycrcb, COLOR_BGR2YCrCb);
	std::vector<Mat> vcChannels;
	split(ycrcb, vcChannels);
	Mat dst;
	/*
	均衡化灰度图像的直方图。
	该算法对图像的亮度进行归一化，提高了图像的对比度。
	输入为8位单通道图像。输出于输入相同大小类型
	*/
	equalizeHist(vcChannels[0], vcChannels[0]);//只能处理灰度图
	merge(vcChannels, ycrcb);
	cvtColor(ycrcb, dst, COLOR_YCrCb2BGR);
	imshow("RGB图像", image);
	imshow("直方图均衡化", dst);
}

//对直方图进行比较
void QuickDemo::histogram_compare_demo()
{
	//读取图片
	Mat src1 = imread("D:/images/m1.png");
	Mat src2 = imread("D:/images/m2.png");
	Mat src3 = imread("D:/images/pedestrian.png");
	Mat src4 = imread("D:/images/persons.png");

	namedWindow("input1", WINDOW_FREERATIO);
	namedWindow("input2", WINDOW_FREERATIO);
	namedWindow("input3", WINDOW_FREERATIO);
	namedWindow("input4", WINDOW_FREERATIO);
	imshow("input1", src1);
	imshow("input2", src2);
	imshow("input3", src3);
	imshow("input4", src4);

	//转换hsv
	Mat hsv1, hsv2, hsv3, hsv4;
	cvtColor(src1, hsv1, COLOR_BGR2HSV);
	cvtColor(src2, hsv2, COLOR_BGR2HSV);
	cvtColor(src3, hsv3, COLOR_BGR2HSV);
	cvtColor(src4, hsv4, COLOR_BGR2HSV);

	//输出直方图
	int h_bins = 60;
	int sbins = 64;
	int histSize[] = {h_bins, sbins};
	float h_ranges[] = { 0, 180 };
	float s_ranges[] = { 0, 256 };
	const float* ranges[] = { h_ranges , s_ranges };
	int channels[] = { 0, 1 };//处理两个通道
	Mat hist1, hist2, hist3, hist4;
	calcHist(&hsv1, 1, channels, Mat(), hist1, 2, histSize, ranges, true, false);
	calcHist(&hsv2, 1, channels, Mat(), hist2, 2, histSize, ranges, true, false);
	calcHist(&hsv3, 1, channels, Mat(), hist3, 2, histSize, ranges, true, false);
	calcHist(&hsv4, 1, channels, Mat(), hist4, 2, histSize, ranges, true, false);

	//归一化处理
	normalize(hist1, hist1, 0, 1, NORM_MINMAX, -1, Mat());
	normalize(hist2, hist2, 0, 1, NORM_MINMAX, -1, Mat());
	normalize(hist3, hist3, 0, 1, NORM_MINMAX, -1, Mat());
	normalize(hist4, hist4, 0, 1, NORM_MINMAX, -1, Mat());
	
	//直方图比较
	for (int i = 0; i < 4; i++)
	{
		int compare_method = i;//四种算法
		/*
		CV_EXPORTS_W double compareHist( InputArray H1, InputArray H2, int method );
		返回值double类型的数据表示我们用第三个参数比较两幅直方图相似性之后得出来的结论，
		参数H1,H2就是两幅直方图的数据，对于数据而言，比较他们的相似性相关性计算。
		我要比较两个两幅直方图，就是有两堆数据在哪里你要进行比较，那么你最先想到的就是数据相似关的计算。
		则第三个参数就是数据相关性计算的方法类别。HistCompMethods{ Correlation、 Chi-Square、 Intersection 、Bhattacharyya distance }
		*/
		double src1_src2 = compareHist(hist1, hist2, compare_method);
		double src3_src4 = compareHist(hist3, hist4, compare_method);
		printf(" Method [%d]  : src1_src2 : %f, src3_src4: %f,  \n", i, src1_src2, src3_src4);
	}
}

//计算卷积
void QuickDemo::blur_demo(Mat &image)
{
	Mat dst;
	//namedWindow("卷积", WINDOW_FREERATIO); 
	//卷积核越大图像越模糊  根据Size的传入还可以进行水平方向卷积Size(15, 1)，竖直方向卷积Size(1,15
	blur(image, dst, Size(15, 15), Point(-1, -1));
	imshow("卷积", dst);
}
//计算高斯模糊
void QuickDemo::gaussian_blur_demo(Mat &image)
{
	Mat dst;
	//卷积核的大小，注意一定要是基数 偶数就是错误的(违反了高斯中心化的原则)
	//sigma  当窗口设置Size(0,0)的时候opencv就会从sigma反算窗口大小，
	//当窗口大小已经设定一个值之后那么sigma这边无论设什么都没有效果，他会从窗口计算得到sigma的
	//并且窗口或者sigma都是值越大图形越模糊，sigma对图形的模糊效果更加明显所以很多时候都会设置size而是直接设计sigma的来查看模糊效果
	GaussianBlur(image, dst, Size(5, 5), 15);
	imshow("高斯模糊", dst);
}
//计算双边高斯卷积
void QuickDemo::Bilateralgaussian_blur_demo(Mat &image)
{
	Mat dst;
	//100表示色彩的卷积核 要大一点
	//10表示空间距离的卷积核
	bilateralFilter(image, dst, 0, 100, 10);
	imshow("高斯模糊", dst);
}

//人脸识别的demo
void QuickDemo::face_detection_demo()
{
	std::string rootdir = "D:/opencv4.4/opencv/sources/samples/dnn/face_detector/";
	//读取dnn里面的Tensorflow模型  返回一个网络文件
	cv::dnn::Net net = cv::dnn::readNetFromTensorflow(rootdir+"opencv_face_detector_uint8.pb", rootdir + "opencv_face_detector.pbtxt");
	VideoCapture capture(0);
	Mat frameVedio;
	while (true)
	{
		capture.read(frameVedio);
		if (frameVedio.empty())
			break;
		//模型需要的大小 均值 参数 可以查看dnn下的models.yml文件 
		Mat blob = cv::dnn::blobFromImage(frameVedio, 1.0, Size(300, 300), Scalar(104, 177, 123), false, false);//读取模型
		net.setInput(blob);//准备数据   blob就是NCWH (多少个，通道数，宽高)
		Mat probs = net.forward();//完成推理    出来的结果是多少张图像有个编号imageindex、第几个批次的，有多少个框，每个框有七列。
		Mat detectionMat(probs.size[2], probs.size[3], CV_32F, probs.ptr<float>());//宽，高，数据类型，数据地址
		//解析结果  
		for (int i = 0; i < detectionMat.rows; i++)
		{
			//取值七个值 0类型 1自己的index  2自己的得分得分越高越可能是人脸  34 左上角点的坐标  56右下角点的坐标
			float confidence = detectionMat.at<float>(i, 2);
			if (confidence > 0.5)//大于0.5就可能是人脸概率
			{
				//因为预测出来的数是0-1之间的，要乘以实践宽高 才是真正的坐标值
				int x1 = static_cast<int>(detectionMat.at<float>(i, 3)*frameVedio.cols);
				int y1 = static_cast<int>(detectionMat.at<float>(i, 4)*frameVedio.rows);
				int x2 = static_cast<int>(detectionMat.at<float>(i, 5)*frameVedio.cols);
				int y2 = static_cast<int>(detectionMat.at<float>(i, 6)*frameVedio.rows);
				Rect rect(x1, y1, x2-x1, y2-y1);
				rectangle(frameVedio, rect, Scalar(0, 0, 255), 2, 8, 0);
			}
		}
		imshow("人脸检测演示", frameVedio);
		int c = waitKey(10);
		if (c == 27)
			break;
	}

	capture.release();//摄像头资源需要释放
}

//视频绿布切割背景替换
void QuickDemo::beijing_tihuan_demo()
{
	VideoCapture captureCamear("D:/01.mp4");
	//get视频属性 注意也是可以set设置的 但是注意如果是摄像头的话他硬件是否支持set的参数
	int frame_width = captureCamear.get(CAP_PROP_FRAME_WIDTH);
	int frame_height = captureCamear.get(CAP_PROP_FRAME_HEIGHT);
	int frame_counts = captureCamear.get(CAP_PROP_FRAME_COUNT);
	int fps = captureCamear.get(CAP_PROP_FPS);
	std::cout << "frame_width = " << frame_width << std::endl;
	std::cout << "frame_height = " << frame_height << std::endl;
	std::cout << "frame_counts = " << frame_counts << std::endl;
	std::cout << "fps = " << fps << std::endl;

	//CAP_PROP_FOURCC  获取原来的编码类型   注意size的大小不能变
	VideoWriter writer("D:/test.mp4", captureCamear.get(CAP_PROP_FOURCC), fps, Size(frame_width, frame_height), true);
	VideoCapture Camerwriter("D:/lane.avi");
	Mat frameCamear;
	Mat frameVedio;
	while (true)
	{
		captureCamear.read(frameCamear);//读取视频 每一帧 从而操作视频就是操作图像了
		Camerwriter.read(frameVedio);
		Mat hsv;
		cvtColor(frameCamear, hsv, COLOR_BGR2HSV);
		Mat mask;
		inRange(hsv, Scalar(35, 43, 46), Scalar(77, 255, 255), mask);//输入hsv图像、 根据绿色作为分界则传入hsv绿色的hsv最大最下值
		//imshow("inRange mask", mask);//只有黑白  把绿色都变成1白色 其他变成0黑色
		resize(frameVedio, frameVedio, Size(frame_width, frame_height), 0, 0, INTER_LINEAR);
		bitwise_not(mask, mask);//取反 黑变白 白变黑   就是相当于把绿色部分变成0黑色、人部分变成1白色
		frameCamear.copyTo(frameVedio, mask);
		writer.write(frameVedio);//写入文件
		if (frameVedio.empty())
		{
			break;
		}
		imshow("frame", frameVedio);
		int c = waitKey(10);
		if (c == 27)
			break;
	}
	//captureVedio.release();
	captureCamear.release();//摄像头资源需要释放
	writer.release();//视频写入变量也需要释放资源
}

//加入高斯模糊的绿布抠图替换
Mat background_01;
Mat background_02;
Mat replace_and_blend(Mat &frame, Mat &mask) {
	Mat result = Mat::zeros(frame.size(), frame.type());
	int h = frame.rows;
	int w = frame.cols;
	int dims = frame.channels();

	// replace and blend
	int m = 0;
	double wt = 0.0;
	int r = 0, g = 0, b = 0;

	int b1 = 0, g1 = 0, r1 = 0;
	int b2 = 0, g2 = 0, r2 = 0;

	for (int row = 0; row < h; row++) {
		uchar* current = frame.ptr<uchar>(row);
		uchar* bgrow = background_01.ptr<uchar>(row);
		uchar* maskrow = mask.ptr<uchar>(row);
		uchar* targetrow = result.ptr<uchar>(row);
		for (int col = 0; col < w; col++) {
			m = *maskrow++;
			if (m == 255) { // 背景
				*targetrow++ = *bgrow++;
				*targetrow++ = *bgrow++;
				*targetrow++ = *bgrow++;
				current += 3;
			}
			else if (m == 0) {
				*targetrow++ = *current++;
				*targetrow++ = *current++;
				*targetrow++ = *current++;
				bgrow += 3;
			}
			else {
				// 背景像素
				b1 = *bgrow++;
				g1 = *bgrow++;
				r1 = *bgrow++;

				// 目标前景像素
				b2 = *current++;
				g2 = *current++;
				r2 = *current++;

				// 混合权重
				wt = m / 255.0;

				// 混合
				b = b1*wt + b2*(1.0 - wt);
				g = g1*wt + g2*(1.0 - wt);
				r = r1*wt + r2*(1.0 - wt);

				*targetrow++ = b;
				*targetrow++ = g;
				*targetrow++ = r;
			}
		}
	}

	return result;
}
void QuickDemo::beijing_tihuan_demo1()
{
	background_01 = imread("D:/8519639.jpg");
	background_02 = imread("D:/2.png");
	resize(background_02, background_02, Size(background_01.cols, background_01.rows));
	VideoCapture capture;
	capture.open("D:/01.mp4");
	if (!capture.isOpened()) {
		printf("could not load video file...\n");
		return ;
	}
	VideoCapture captureTwo;
	captureTwo.open("D:/dushuhu.mp4");


	char* title = "input video";
	char* matting_title = "video matting result";
	namedWindow(title, WINDOW_AUTOSIZE);
	namedWindow(matting_title, WINDOW_AUTOSIZE);
	Mat frame, hsv, mask;
	Mat frame2;
	int count = 0;
	Size S = Size((int)capture.get(CAP_PROP_FRAME_WIDTH),
		(int)capture.get(CAP_PROP_FRAME_HEIGHT));
	while (capture.read(frame)) {
		if (captureTwo.read(frame2)) {
			resize(frame2, background_01, frame.size());
		}
		else {
			background_02.copyTo(background_01);//如果背景视频播放完毕就是要背景 图片替代
		}
		cvtColor(frame, hsv, COLOR_BGR2HSV);
		inRange(hsv, Scalar(35, 43, 46), Scalar(155, 255, 255), mask);

		// 形态学腐蚀操作
		//Mat k = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
		//morphologyEx(mask, mask, MORPH_CLOSE, k);
		//erode(mask, mask, k);
		GaussianBlur(mask, mask, Size(3, 3), 0, 0);

		Mat result = replace_and_blend(frame, mask);
		char c = waitKey(1);
		if (c == 27) {
			break;
		}
		imshow(title, frame);
		imshow(matting_title, result);
	}

	waitKey(0);
	return ;

}



QuickDemo::QuickDemo()
{
}


QuickDemo::~QuickDemo()
{
}
