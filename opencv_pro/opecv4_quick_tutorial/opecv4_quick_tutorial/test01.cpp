#include<opencv2/opencv.hpp>
#include <iostream>
#include "QuickDemo.h"

using namespace cv;//opencv�������ռ�
using namespace std;

int main(int argc, char** argv)
{
	//Mat src = imread("C:/Users/20531/Desktop/2.png");  //Ĭ��IMREAD_COLOR��ɫ�ģ�3 channel BGR
	//Mat src = imread("C:/Users/20531/Desktop/1/9.png",IMREAD_GRAYSCALE);//��ʾ�Ҷ�ͼ �Ǳ��������ת����
	/*if (src.empty())
	{
		cout << "imread faile" << endl;
		getchar();
		return -1;
	}*/
	//cout << "Mat src  deep = " << src.depth() << endl;
	
	//��ʵ�Ǵ���Ĭ�ϵĴ��ڣ�ֻ�������õ�ģʽ��WINDOW_AUTOSIZE  ����ͼƬ��С�趨�ģ���˴��ڿ����޷�չʾ��ȫ
	//namedWindow("���봰��", WINDOW_FREERATIO);//����һ������ ��������Ϊ�������ô�Сģʽ
	//imshow("���봰��", src);//ע��imshow��ʱ���Ҫָ����ʾ����Ӧ������

	/*QuickDemo qd;
	qd.beijing_tihuan_demo1();*/
	QuickDemo qd;
	Mat src = imread("D:/1.png");
	qd.histogram_compare_demo();
	
	waitKey(0);
	destroyAllWindows();
	return 0;
}