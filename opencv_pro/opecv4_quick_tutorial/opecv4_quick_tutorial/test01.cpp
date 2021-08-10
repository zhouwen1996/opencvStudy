#include<opencv2/opencv.hpp>
#include <iostream>
#include "QuickDemo.h"

using namespace cv;//opencv的命名空间
using namespace std;

int main(int argc, char** argv)
{
	//Mat src = imread("C:/Users/20531/Desktop/2.png");  //默认IMREAD_COLOR彩色的，3 channel BGR
	//Mat src = imread("C:/Users/20531/Desktop/1/9.png",IMREAD_GRAYSCALE);//显示灰度图 是编解码器内转换的
	/*if (src.empty())
	{
		cout << "imread faile" << endl;
		getchar();
		return -1;
	}*/
	//cout << "Mat src  deep = " << src.depth() << endl;
	
	//其实是存在默认的窗口，只是他设置的模式是WINDOW_AUTOSIZE  根据图片大小设定的，因此窗口可能无法展示完全
	//namedWindow("输入窗口", WINDOW_FREERATIO);//创建一个窗口 并且设置为自由设置大小模式
	//imshow("输入窗口", src);//注意imshow的时候就要指定显示到对应窗口上

	/*QuickDemo qd;
	qd.beijing_tihuan_demo1();*/
	QuickDemo qd;
	Mat src = imread("D:/1.png");
	qd.histogram_compare_demo();
	
	waitKey(0);
	destroyAllWindows();
	return 0;
}