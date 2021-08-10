#include "QuickDemo.h"
#include <opencv2/dnn.hpp>
#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>
//ʵ��BGRת�ҶȺ�hsv
void QuickDemo::colorSpace_Demo(Mat &image)
{
	Mat gray;
	Mat hsv;
	cvtColor(image, gray, COLOR_BGR2GRAY);//�������������Ը������src��dst�Լ�ѡ��
	cvtColor(image, hsv, COLOR_BGR2HSV);
	imshow("�Ҷ�", gray);
	imshow("HSV", hsv);
	imwrite("hsv.png",hsv);//�е��������� ��ֻ����ǰ����
	imwrite("gray.png", gray);
	return;
}
//Mat�Ĵ��� clone   copyTo   zeros   ones  Scalar  =
void QuickDemo::mat_creat_Demo(Mat &image)
{
	Mat mClone;
	Mat mCopy;
	mClone = image.clone();//��¡
	image.copyTo(mCopy);//����

	//�����հ�mat  CV_8UC1��ʾ8λ �޷������� channelͨ��Ϊ1
	Mat mEmpty = Mat::zeros(Size(8,8),CV_8UC1);//������СΪ8x8�ĵ�ͨ���Ŀ�mat
	Mat mOnes = Mat::ones(Size(8, 8), CV_8UC3);//ע��ʹ��ones��ʼ��Ϊ1��ʱ����ֻ��ÿ�����صĵ�һ��ͨ����ʼ��Ϊ1����������0
	std::cout << "ones ��Size(8,8)  CV_8UC3:" << mOnes << std::endl;
	std::cout << "Size(8,8)  CV_8UC1:" <<  mEmpty << std::endl;
	std::cout << "width=" << mEmpty.cols << ",height=" << mEmpty.rows << ",channele=" << mEmpty.channels() << std::endl;
	std::cout << "====================" << std::endl;
	Mat mEmptyC3 = Mat::zeros(Size(8, 8), CV_8UC3);//������СΪ8x8��3ͨ���Ŀ�mat
	std::cout << "Size(8,8)  CV_8UC3:" << mEmptyC3 << std::endl;
	std::cout << "width=" << mEmptyC3.cols << ",height=" << mEmptyC3.rows << ",channele=" << mEmptyC3.channels() << std::endl;

	//��ֵ����
	mEmptyC3 = 127;//���ָ�ֵ����Ҳͬ��ֻ�ǻ��ÿ�����صĵ�һ��ͨ����ֵΪ127�����Ĳ���
	std::cout << "mEmptyC3 = 127;:" << mEmptyC3 << std::endl;

	//������ɫ������
	mEmptyC3 = Scalar(127, 127, 127);//�����Ҫ����ÿ��ͨ����Ҫʹ��Scalar��
	std::cout << "mEmptyC3 = Scalar(127, 127, 127);:" << mEmptyC3 << std::endl;

	imshow("��������", mEmptyC3);//ע��imshow֧��8λ�򸡵������� �����Ƶ�

	//��֤��ֵ���� ��ʵ���������ƣ�ֻ��ָ�븳ֵ�����=������ı�ԭ��mat
	//����clone��copyto�ǲ����µ�������������Ӱ��ԭ���ġ�
	Mat mEqualOpr = mEmptyC3;
	mEqualOpr = Scalar(0, 255, 255);
	imshow("��������1", mEmptyC3);

	return;
}
//��ͼ�����صĶ�д����
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
			if (channel == 1)//��ͨ�� �Ҷ�ͼ
			{
				*current_row++ = 255 - *current_row;//��֤������255֮�䣬���ݲ�Խ����
			}
			else if (channel == 3)//��ͨ��
			{
				//ÿ�η���һ���ֽڣ����ҽ���++�ƶ�
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
	//		if (channel == 1)//��ͨ�� �Ҷ�ͼ
	//		{
	//			int p = image.at<uchar>(row, cols);//������ uchar�޷����ֽ����� ת��Ϊint
	//			image.at<uchar>(row, cols) = 255 - p;//��֤������255֮�䣬���ݲ�Խ����
	//		}
	//		else if (channel == 3)//��ͨ��
	//		{
	//			Vec3b bgr = image.at<Vec3b>(row, cols);//��Vec3b�������������� һ�ζ�ȡ����ֵ���ض���Vec<uchar, 3>
	//			//д
	//			image.at<Vec3b>(row, cols)[0] = 255 - bgr[0];
	//			image.at<Vec3b>(row, cols)[1] = 255 - bgr[1];
	//			image.at<Vec3b>(row, cols)[2] = 255 - bgr[2];
	//		}
	//	}
	//}
	imshow("���ض�д��ʾ",image);
}
//Mat���������� �Ӽ��˳�����Ӧ��API
void QuickDemo::opreat_demo(Mat &image)
{
	Mat dst;
	////Scalar��ʾ����
	dst = image + Scalar(50, 50, 50);//Ҳ����ʹ��opencv�Դ�api��add()����
	imshow("�ӷ�����", dst);
	dst = image - Scalar(50, 50, 50);
	imshow("��������", dst);
	dst = image / Scalar(4, 4, 4);//Ҳ����ʹ��divide()����
	imshow("��������", dst);
	/*dst = image * Scalar(2, 2, 2);ֱ�ӳ˷�����������������opencv���ṩ��ר�ŵĳ˷�����
	imshow("�˷�������", dst);*/
	//opencv�ṩ�ĳ˷����� ���Ὣ������Χ�������Զ���ȡ 
	//ʹ��saturate_cast<uchar>���� С��0����0 ����255����255

	//ע���贴����С��image��ͬ��mat���г˷�  �������� ֱ��ScalarҲ����
	//Mat m = Mat::zeros(image.size(), image.type());
	//m = Scalar(2, 2, 2);
	multiply(image, Scalar(2, 2, 2), dst);
	imshow("�˷�����", dst);

	//�Զ���ӷ�����
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
			//ÿ�η���һ���ֽڣ����ҽ���++�ƶ�
			//�ؼ� saturate_cast  ��֤���������ڷ�Χ��
			*(current_dst++) = saturate_cast<uchar>(*current_row++ + *current_m++);
			*(current_dst++) = saturate_cast<uchar>(*current_row++ + *current_m++);
			*(current_dst++) = saturate_cast<uchar>(*current_row++ + *current_m++);
		}
	}
	imshow("�Զ���ӷ�����", dst);

	return;
}

//���int b�������ȵ�����������ֵ
//void *userdata  �κ����͵�ָ�� ֻ��Ҫ����ת��
static void on_track(int b, void *userdata)
{
	Mat image = *((Mat *)userdata);
	Mat mTemp = Mat::zeros(image.size(), image.type());
	Mat dst = Mat::zeros(image.size(), image.type());
	addWeighted(image, 1.0, mTemp, 0, b, dst);//ͼ���� ���ݸ���Ȩ��
	imshow("���ȵ���", dst);
}
static void on_constrast(int b, void *userdata)
{
	Mat image = *((Mat *)userdata);
	Mat mTemp = Mat::zeros(image.size(), image.type());
	Mat dst = Mat::zeros(image.size(), image.type());
	double constrat = b / 100.0;
	addWeighted(image, constrat, mTemp, 0.0, 0, dst);
	imshow("���ȵ���", dst);
}
//������ʵ�����ȺͶԱȶȵĵ���
void QuickDemo::tracking_bar_demo(Mat &image)
{
	int lightness = 50;//����ֵ
	namedWindow("���ȵ���", WINDOW_AUTOSIZE);
	int max_value = 100;
	int constract_value = 100;
	//on_track  �ص�����
	createTrackbar("Value Bar:", "���ȵ���", &lightness, max_value, on_track, (void *)(&image));
	createTrackbar("constrat Bar:", "���ȵ���", &constract_value, 200, on_constrast, (void *)(&image));
	//����Ҫ����һ�Σ�����տ�ʼ��û��ͼ��ģ�Ҫ������У��ڶ�������û�оʹ�0
	on_track(50, &image);
	return;
}
//���ռ����¼�
void QuickDemo::key_demo(Mat &image)
{
	Mat dst = Mat::zeros(image.size(), image.type());
	while (true)
	{
		//��ԶҪ�ǵ�һ��������Ƶ������ʱ��waitKeyһ��Ҫ����1
		int c = waitKey(100);//Waits for a pressed key. �ȴ�100ms
		//std::cout << c << std::endl;  ��ʱ�Ȳ��԰���ʲô������opencv�ж�Ӧ��ֵ
		if (c == 27)//esc �˳�27
		{
			break;
		}
		else if (c == 49)//���ͼƬ������1���лҶ�ת��
		{
			std::cout << "you enter key #1" << std::endl;
			cvtColor(image, dst, COLOR_BGR2GRAY);
		}
		else if (c == 50)//���ͼƬ������2����hsvת��
		{
			std::cout << "you enter key #2" << std::endl;
			cvtColor(image, dst, COLOR_BGR2HSV);
		}
		else if (c == 51)//���ͼƬ������3������������ת��
		{
			std::cout << "you enter key #3" << std::endl;
			add(image, Scalar(50, 50, 50), dst);
		}
		imshow("��ʾ�������ͼƬ", dst);
	}

	return;
}
//ɫ�ʱ� //ʵ��ͼ��ɫ�ʱ仯
void QuickDemo::color_style_demo(Mat &image)
{
	//enum ColormapTypes  ֧�ֵ�20��ɫ�ʿռ�
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
		int c = waitKey(2000);//Waits for a pressed key. �ȴ�100ms
		if (c == 27)//esc �˳�27
		{
			break;
		}
		applyColorMap(image, dst, colorMap[index%19]);
		index++;
		imshow("��ɫ���", dst);
	}

}
//��Matʵ�����ص�λ����
void QuickDemo::bitwise_demo(Mat &image)
{
	Mat m1 = Mat::zeros(Size(256, 256), CV_8UC3);
	Mat m2 = Mat::zeros(Size(256, 256), CV_8UC3);
	Mat m3 = Mat::zeros(Size(256, 256), CV_8UC3);
	rectangle(m1,Rect(100, 100, 80, 80), Scalar(255, 255, 0), -1, LINE_8, 0);//-1��ʾ�����Σ�LINE_8��ʾ������Χ8������
	rectangle(m2, Rect(150, 150, 80, 80), Scalar(0, 255, 255), -1, LINE_8, 0);
	rectangle(m3, Rect(0, 0, 80, 80), Scalar(255, 0, 255),5, LINE_8, 0);//���� �൱�����
	imshow("m1", m1);
	imshow("m2", m2);
	imshow("m3", m3);

	Mat dst;
	bitwise_and(m1, m2, dst);//�൱�ڽ���
	imshow("����λ������", dst);
	bitwise_or(m1, m2, dst);//ȫ��  
	imshow("����λ������", dst);
	bitwise_not(image, dst);
	//dst = ~image;//Ҳ�ǿ��Ե�
	imshow("����λ������", dst);
	bitwise_xor(m1, m2, dst);
	imshow("����λ�������", dst);
	return;
}
//ͼ��ͨ���ķ���ϲ�
void QuickDemo::channels_demo(Mat &image)
{
	//ͼ�����split����
	std::vector<Mat> mv;
	//opencv˳����BGR��
	split(image, mv); //���������ͨ����Ӧ������ɫ
	imshow("��ɫ", mv[0]);
	imshow("��ɫ", mv[1]);
	imshow("��ɫ", mv[2]);

	//�ϲ�ͨ����Ŀ��mat
	Mat dst;
	mv[1] = 0;//ֻ������ɫ
	mv[2] = 0;
	merge(mv, dst);
	imshow("ֻ��ʾ��ɫ", dst);

	//��Ͻ���ͨ��
	int from_to[] = {0,2, 1,1, 2,0};//ͨ�����������ﵽ����  ��һ��0ͨ�����ڶ���2ͨ��
	mixChannels(&image, 1, &dst, 1, from_to, 3);//֧�ֶ���ͼƬ  1��ʾ������ͼƬ  3��ʾ�м���ͨ����������
	imshow("ͨ�����", dst);
}

//ɫ�ʿռ��ת��
void QuickDemo::inrange_demo(Mat &image)
{
	Mat hsv;
	cvtColor(image, hsv, COLOR_BGR2HSV);
	Mat mask;
	/*
	inRange��ʵ�ֶ�ֵ������,
	��Ҫ�ǽ���������ֵ�ڵ�����ֵ����Ϊ��ɫ��255������������ֵ�����ڵ�����ֵ����Ϊ��ɫ��0����
	�ù���������֮��������˫��ֵ��������
	*/
	inRange(hsv, Scalar(35, 43, 46), Scalar(77, 255, 255), mask);//����hsvͼ�� ������ɫ��Ϊ�ֽ�����hsv��ɫ��hsv�������ֵ
	imshow("inRange mask", mask);//ֻ�кڰ�  ����ɫ�����1��ɫ �������0��ɫ

	Mat reaback = Mat::zeros(image.size(), image.type());
	reaback = Scalar(40, 40, 200);//���
	bitwise_not(mask, mask);//ȡ�� �ڱ�� �ױ��   �����൱�ڰ���ɫ���ֱ��0��ɫ���˲��ֱ��1��ɫ
	imshow("bitwise_not mask", mask);
	/*
	//mask����˼����image��copy��ʱ��ֻ�����ز�Ϊ0�ĵ�Ż�copy��reaback��ȥ
	�൱��ֻ�˲��ֱ��1��ɫ���ִ�image�ϵ�����ȥ����������
	�����ǰ�image���������򿽱���reaback������
	*/
	image.copyTo(reaback, mask);
	imshow("roi������ȡ", reaback);
}
//��������ֵͳ��
void QuickDemo::pixel_statistic_demmo(Mat &image)
{
	double minv, maxv;//ע����double����
	Point minLoc, maxLoc;//�����С�ĵ�ַ
	std::vector<Mat> mv;
	split(image, mv);
	for (int i = 0; i < mv.size(); i++)
	{
		minMaxLoc(mv[i], &minv, &maxv, &minLoc, &maxLoc, Mat());//������������ǵ�ͨ���ġ�����split
		std::cout << "minvalue:" << minv << "  maxvalue:" << maxv << std::endl;
	}
	
	Mat mean, stddev;
	meanStdDev(image,mean,stddev);//���ĸ�����mask����iro�������������
	std::cout << "mean:" << mean << std::endl;
	std::cout << "mean[0]:" << mean.at<double>(0) << std::endl;
	//����С����ͼ��ĶԱȶȲ���ȵ͡���Ч��Ϣ��
	//�����ͼ��������У����Ը��ݷ���ֵС��ʾ��Χ������С �Ӷ��ǿ��Թ��˵�һЩ������
	std::cout << "stddev:" << stddev << std::endl;
}

//������״����
void QuickDemo::drawing_demo(Mat &image)
{
	//�����ԭ���Ǵ����Ͻ�Ϊ0 0
	//���ƾ����ǿ��������Ͷ����
	Rect rect;
	rect.x = 150;
	rect.y = 20;
	rect.width = 70;
	rect.height = 100;
	
	Mat bg = Mat::zeros(image.size(), image.type());
	//rectangle(bg, rect, Scalar(0, 0, 255), 5, 0);
	rectangle(bg, rect, Scalar(0, 0, 255), -1, 0);//thickness�����ĳ�С��0���ʾ���
	circle(bg, Point(200, 200), 50, Scalar(255, 0, 0), -1, 0);//��Բ
	line(bg, Point(100, 100), Point(255, 255), Scalar(0,0,0),8, 8, 0);//lineTypeͼ��������
	RotatedRect rrt;//��Բ
	rrt.center = Point(300,300);
	rrt.size = Size(50,100);
	rrt.angle = 0;
	ellipse(bg, rrt, Scalar(0, 255, 255), 2, 8);
	Mat dst;
	addWeighted(image, 0.7, bg, 0.3, 0, dst);//imageռ��0.7��bgռ��0.3 ����

	imshow("���Ƽ���", dst);
}
//��������漴����
void QuickDemo::randomdrawing_demo(Mat &image)
{
	Mat canvas = Mat::zeros(Size(500, 500), CV_8UC3);
	int w = canvas.cols;
	int h = canvas.rows;
	RNG rng(12345);//��������� �������� һ�㴫��ʱ��
	while (true)
	{
		int c = waitKey(10);
		if (c == 27)
		{
			break;
		}
		int x1 = rng.uniform(0, w);//��0 - w��Χ�ڲ���һ�������
		int y1 = rng.uniform(0, h);
		int x2 = rng.uniform(0, w);//��0 - w��Χ�ڲ���һ�������
		int y2 = rng.uniform(0, h);
		int b = rng.uniform(0, 255);
		int g = rng.uniform(0, 255);
		int r = rng.uniform(0, 255);
		//canvas = Scalar(0, 0, 0);ÿ�λ������� �ﵽÿ��ͼ��ֻ��һ����
		line(canvas, Point(x1, y1), Point(x2, y2), Scalar(b, g, r), 1, LINE_AA, 0);//lineTypeͼ��������
		imshow("�������", canvas);
	}
	return;
}
//���ƶ����
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
	//Ҫʵ�ֱ߿������Ҫע��fillPoly��polylines��˳��
	fillPoly(canvas, vc_pts, Scalar(255, 0, 255), 8, 0);//ֻ�����
	polylines(canvas, vc_pts, true, Scalar(0, 0, 255), 1, LINE_AA, 0);//�����thicknessֻ�ܴ�����0 �������ֻ�ܻ���
	imshow("����λ���", canvas);

	//��ʾ�������κ���  ������䶼����ѡ��
	std::vector<std::vector<Point>> contous;
	contous.push_back(vc_pts);
	//contourIdx������ʾ�ڼ�����-1��ʾ����ʾ����  
	//thickness  ���Դ���-1��ʾ���
	drawContours(canvas, contous, -1, Scalar(255, 0, 0), -1);
	imshow("����λ���1", canvas);

	return;
}
//����������Ӧ
Point sp(-1, -1);
Point ep(-1, -1);
Mat tempImage;
static void on_draw(int event, int x, int y, int flags, void *usrdata)
{
	Mat image = *((Mat *)usrdata);
	if (event == EVENT_LBUTTONDOWN)//�����������¼�
	{
		sp.x = x;
		sp.y = y;
		std::cout << "start Point: " << sp << std::endl;
	}
	else if (event == EVENT_LBUTTONUP)//����ɿ�
	{
		ep.x = x;
		ep.y = y;
		int dx = ep.x - sp.x;
		int dy = ep.y - sp.y;
		if (dx > 0 && dy > 0)
		{
			Rect box(sp.x, sp.y, dx, dy);
			//ע��˳�� ��Ȼ��ȡ������к�ɫ���ο�
			tempImage.copyTo(image);
			imshow("ROI����", image(box));//��ȡ����ѡ������
			rectangle(image, box, Scalar(0, 0, 255), 2);
			imshow("������", image);

			//���´λ��Ƴ�ʼ��
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
				tempImage.copyTo(image);//��֤ÿ�� ����image���������
				rectangle(image, box, Scalar(0, 0, 255), 2);
				imshow("������", image);
			}
		}
		
	}
	return;
}
void QuickDemo::setMouseCallback_demo(Mat &image)
{
	namedWindow("������", WINDOW_AUTOSIZE);
	setMouseCallback("������", on_draw, (void *)&image);
	tempImage = image.clone();
	imshow("������", image);
}

//��������ת������һ������
void QuickDemo::norm_demo(Mat &image)
{
	Mat dst;
	std::cout << image.type() << std::endl;
	image.convertTo(image, CV_32F);//ת��Ϊ32λ�ĸ�����
	std::cout << image.type() << std::endl;//type()�����ֵ��opencv�ض����ö������ֵ
	normalize(image, dst, 1.0, 0, NORM_MINMAX);
	std::cout << dst.type() << std::endl;
	imshow("ͼ�����ݹ�һ��", dst);
}

//ͼ���������ֵ
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
//��ת
void QuickDemo::flip_demo(Mat &image)
{
	Mat dst;
	flip(image, dst, 0);//���·�ת
	imshow("���·�ת", dst);
	flip(image, dst, 1);//����0 ���ҷ�ת
	imshow("���ҷ�ת", dst);
	flip(image, dst, -1);//С��0  �������Ҷ���ת ����180����ת
	imshow("180����ת", dst);
}
//��ת
void QuickDemo::rotate_demo(Mat &image)
{
	Mat dst, M;
	int w = image.cols;
	int h = image.rows;
	M = getRotationMatrix2D(Point2f(w/2, h/2), 45, 1.0);//�õ���ת45�ȵľ���
	//������ת���ͼƬ��С  ����ǵõ���תMat����֪���Ķ�Ӧ��cos��sin
	double cos = abs(M.at<double>(0, 0));
	double sin = abs(M.at<double>(0, 1));
	//������ת����¿��  ���ݼ���֪ʶ 
	int nh = cos*w + sin*h;
	int nw = sin*w + cos*h;
	//����ƫ���� �޸����ĵ�ƫ����  ��ΪwarpAffine��Ҫ�����mat����������
	M.at<double>(0, 2) += (nw/2 - w/2);
	M.at<double>(1, 2) += (nh / 2 - h / 2);
	warpAffine(image, dst, M, Size(nw, nh), INTER_LINEAR, 0, Scalar(255, 0, 0));
	imshow("��ת��ʾ", dst);//û���ڵ���
}
//��Ƶ��ȡ
void QuickDemo::video_demo(Mat &image)
{
	//VideoCapture captureCamear(0);//����0��ʾ��ȡ����ͷ �����Դ�����Ƶ�ļ���ȫ·���ַ���
	/*
	//�����ȡ��Ƶ�ļ���֡���ʧ������Ҫ
	��opencv��װĿ¼D:\opencv\build\x64\vc14\bin�е�opencv_videoio_ffmpeg440_64.dll����
	��������Ŀ��.exe���ڵ��ļ���Debug/Release���С�
	����Ϊ����OpenCV�汾��4.4������ffmpeg440��
	*/
	VideoCapture captureCamear("C:/Users/20531/Desktop/1.mp4");
	//get��Ƶ���� ע��Ҳ�ǿ���set���õ� ����ע�����������ͷ�Ļ���Ӳ���Ƿ�֧��set�Ĳ���
	int frame_width = captureCamear.get(CAP_PROP_FRAME_WIDTH);
	int frame_height = captureCamear.get(CAP_PROP_FRAME_HEIGHT);
	int frame_counts = captureCamear.get(CAP_PROP_FRAME_COUNT);
	int fps = captureCamear.get(CAP_PROP_FPS);
	std::cout << "frame_width = " << frame_width << std::endl;
	std::cout << "frame_height = " << frame_height << std::endl;
	std::cout << "frame_counts = " << frame_counts << std::endl;
	std::cout << "fps = " << fps << std::endl;

	//CAP_PROP_FOURCC  ��ȡԭ���ı�������   ע��size�Ĵ�С���ܱ�
	VideoWriter writer("D:/test.mp4", captureCamear.get(CAP_PROP_FOURCC), fps, Size(frame_width, frame_height), true);

	Mat frameCamear;
	Mat frameVedio;
	while (true)
	{
		captureCamear.read(frameCamear);//��ȡ��Ƶ ÿһ֡ �Ӷ�������Ƶ���ǲ���ͼ����
		//captureVedio.read(frameVedio);
		flip(frameCamear, frameCamear, 1);//���ҷ�תһ�� ��ʵ�ʱ���һ��
		writer.write(frameCamear);//д���ļ�
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
	captureCamear.release();//����ͷ��Դ��Ҫ�ͷ�
	writer.release();//��Ƶд�����Ҳ��Ҫ�ͷ���Դ
}
//��ȡֱ��ͼ
void QuickDemo::histogram(Mat &image)
{
	//�ָ�ͨ��
	std::vector<Mat> bgr_plane;
	split(image, bgr_plane);
	//�����������
	const int channels[1] = { 0 };
	const int bins[1] = { 256 };//ֱ��ͼ��ȡֵ����
	float hranges[2] = { 0, 255 };//ֱ��ͼ��ȡֵ��Χ
	const float* ranges[1] = {hranges};//��Ϊ�ӿڿ���֧�ֶ�ά�� ����ͼ��
	Mat b_hist;
	Mat g_hist;
	Mat r_hist;

	//����ֱ��ͼ
	calcHist(&bgr_plane[0], 1, 0, Mat(), b_hist, 1, bins, ranges);
	calcHist(&bgr_plane[1], 1, 0, Mat(), g_hist, 1, bins, ranges);
	calcHist(&bgr_plane[2], 1, 0, Mat(), r_hist, 1, bins, ranges);

	//��ʾֱ��ͼ
	int hist_w = 512;
	int hist_h = 400;
	int bin_w = cvRound((double)hist_w/bins[0]);//ÿ��bin��256�����ܿ�ȳ������õ�ÿ���Ҷ�ֵ��ͼ����ռ�������ص㣬������Ҫ��ͼ��
	Mat hisImage = Mat::zeros(hist_h, hist_w, CV_8UC3);//����ֱ��ͼ�ĵײ�

	//��һ������ ��Ϊ����ͨ�����ֵ���ͬ�Ҷ�ֵ������ֵ̫���������Ҫ��һ����һ�η�Χ�� (�ײ��߶ȷ�Χ��ô��)����ʾ��һ��ͼƬ��
	normalize(b_hist, b_hist, 0, hisImage.rows, NORM_MINMAX, -1, Mat());
	normalize(g_hist, g_hist, 0, hisImage.rows, NORM_MINMAX, -1, Mat());
	normalize(r_hist, r_hist, 0, hisImage.rows, NORM_MINMAX, -1, Mat());
	//����ֱ��ͼ����
	for (int i = 1; i < bins[0]; i++)
	{
		//������궼�ǻ�����Ļ����� ���Ҫ��ת�� hist_h -cvRound(b_hist.at<float>(i-1)))
		line(hisImage, Point(bin_w*(i-1), hist_h -cvRound(b_hist.at<float>(i-1))),
		Point(bin_w*(i), hist_h-cvRound(b_hist.at<float>(i))), Scalar(255,0,0),2,8,0);
		line(hisImage, Point(bin_w*(i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(g_hist.at<float>(i))), Scalar(0, 255, 0), 2, 8, 0);
		line(hisImage, Point(bin_w*(i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(r_hist.at<float>(i))), Scalar(0, 0, 255), 2, 8, 0);
	}
	//��ʾֱ��ͼ
	namedWindow("Histogram Deemo", WINDOW_AUTOSIZE);
	imshow("Histogram Deemo", hisImage);
}
//��ȡ��άֱ��ͼ
void QuickDemo::histogram_2d_demo(Mat &image)
{
	//2Dֱ��ͼ
	Mat hsv, hsv_hist;
	cvtColor(image, hsv, COLOR_BGR2HSV);
	int hbins = 30;//h�ĻҶ�ֻ��0-179��һ��180���Ҷ�ֵ��30���Ҷ�ֵΪһ����λͳ���ڸ÷�Χ�ڵ�����Ƶ��
	int sbins = 32;//s�ĻҶ�ֵʵʱ0-255
	int hist_bins[] = {hbins, sbins};//2d������bins���ý�ȥ
	float h_range[] = {0, 180};//�Ҷ�ֵ��ȡֵ��Χ
	float s_range[] = { 0, 256 };
	const float* hs_range[] = {h_range, s_range};
	int hs_channels[] = { 0, 1 };
	//hsv ֻ��һ��ͼ��  ��0���͵�һ��ͨ����mask������֮ǰ��һ�� ֻ�Է�0��������  ������mat  2ά�� ��1��2��ͨ�����ٸ�bins  ��1��2��ͨ�����ٸ�ȡֵ��Χ
	//��������ڵó�ÿ���Ҷ�ֵ��Ӧ�����ص�ĸ���
	calcHist(&hsv, 1, hs_channels, Mat(), hsv_hist, 2, hist_bins, hs_range, true, false);
	//2ά��һͼͼ������ ������Ҫ���й�һ������
	double maxVal = 0;
	minMaxLoc(hsv_hist, 0, &maxVal, 0, 0);//���ֵ
	int scale = 10;
	Mat hist2d_image = Mat::zeros(sbins*scale, hbins*scale, CV_8UC3);//�����հ�ͼ�� ���������������뼴��
	for (int h = 0; h < hbins; h++)
	{
		for (int s = 0; s < sbins; s++)
		{
			float binVal = hsv_hist.at<float>(h, s);
			int intensity = cvRound(binVal * 255 / maxVal);//ȡ��
			rectangle(hist2d_image, Point(h*scale, s*scale),
				Point((h+1)*scale -1, (s+1)*scale -1),
				Scalar::all(intensity), -1);
		}
	}
	applyColorMap(hist2d_image, hist2d_image, COLORMAP_JET);//���ɫ��ͼ
	imshow("H-S Histogram", hist2d_image);
}
//��ȡֱ��ͼ�ľ��⻯
void QuickDemo::histogram_eq_demo(Mat &image)
{
	namedWindow("�Ҷ�ͼ��", WINDOW_FREERATIO);
	namedWindow("ֱ��ͼ���⻯", WINDOW_FREERATIO);//ͼƬ̫����
	Mat gray;
	cvtColor(image, gray, COLOR_BGR2GRAY);//�Ҷ�ͼ��
	imshow("�Ҷ�ͼ��", gray);
	Mat dst;
	equalizeHist(gray, dst);
	imshow("ֱ��ͼ���⻯", dst);
}


//�Բ�ɫͼ�����ֱ��ͼ�ľ��⻯
void QuickDemo::histogram_eqRGB_demo(Mat &image)
{
	namedWindow("RGBͼ��", WINDOW_FREERATIO);
	namedWindow("ֱ��ͼ���⻯", WINDOW_FREERATIO);//ͼƬ̫����
	Mat ycrcb;
	cvtColor(image, ycrcb, COLOR_BGR2YCrCb);
	std::vector<Mat> vcChannels;
	split(ycrcb, vcChannels);
	Mat dst;
	/*
	���⻯�Ҷ�ͼ���ֱ��ͼ��
	���㷨��ͼ������Ƚ��й�һ���������ͼ��ĶԱȶȡ�
	����Ϊ8λ��ͨ��ͼ�������������ͬ��С����
	*/
	equalizeHist(vcChannels[0], vcChannels[0]);//ֻ�ܴ���Ҷ�ͼ
	merge(vcChannels, ycrcb);
	cvtColor(ycrcb, dst, COLOR_YCrCb2BGR);
	imshow("RGBͼ��", image);
	imshow("ֱ��ͼ���⻯", dst);
}

//��ֱ��ͼ���бȽ�
void QuickDemo::histogram_compare_demo()
{
	//��ȡͼƬ
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

	//ת��hsv
	Mat hsv1, hsv2, hsv3, hsv4;
	cvtColor(src1, hsv1, COLOR_BGR2HSV);
	cvtColor(src2, hsv2, COLOR_BGR2HSV);
	cvtColor(src3, hsv3, COLOR_BGR2HSV);
	cvtColor(src4, hsv4, COLOR_BGR2HSV);

	//���ֱ��ͼ
	int h_bins = 60;
	int sbins = 64;
	int histSize[] = {h_bins, sbins};
	float h_ranges[] = { 0, 180 };
	float s_ranges[] = { 0, 256 };
	const float* ranges[] = { h_ranges , s_ranges };
	int channels[] = { 0, 1 };//��������ͨ��
	Mat hist1, hist2, hist3, hist4;
	calcHist(&hsv1, 1, channels, Mat(), hist1, 2, histSize, ranges, true, false);
	calcHist(&hsv2, 1, channels, Mat(), hist2, 2, histSize, ranges, true, false);
	calcHist(&hsv3, 1, channels, Mat(), hist3, 2, histSize, ranges, true, false);
	calcHist(&hsv4, 1, channels, Mat(), hist4, 2, histSize, ranges, true, false);

	//��һ������
	normalize(hist1, hist1, 0, 1, NORM_MINMAX, -1, Mat());
	normalize(hist2, hist2, 0, 1, NORM_MINMAX, -1, Mat());
	normalize(hist3, hist3, 0, 1, NORM_MINMAX, -1, Mat());
	normalize(hist4, hist4, 0, 1, NORM_MINMAX, -1, Mat());
	
	//ֱ��ͼ�Ƚ�
	for (int i = 0; i < 4; i++)
	{
		int compare_method = i;//�����㷨
		/*
		CV_EXPORTS_W double compareHist( InputArray H1, InputArray H2, int method );
		����ֵdouble���͵����ݱ�ʾ�����õ����������Ƚ�����ֱ��ͼ������֮��ó����Ľ��ۣ�
		����H1,H2��������ֱ��ͼ�����ݣ��������ݶ��ԣ��Ƚ����ǵ�����������Լ��㡣
		��Ҫ�Ƚ���������ֱ��ͼ������������������������Ҫ���бȽϣ���ô�������뵽�ľ����������ƹصļ��㡣
		�����������������������Լ���ķ������HistCompMethods{ Correlation�� Chi-Square�� Intersection ��Bhattacharyya distance }
		*/
		double src1_src2 = compareHist(hist1, hist2, compare_method);
		double src3_src4 = compareHist(hist3, hist4, compare_method);
		printf(" Method [%d]  : src1_src2 : %f, src3_src4: %f,  \n", i, src1_src2, src3_src4);
	}
}

//������
void QuickDemo::blur_demo(Mat &image)
{
	Mat dst;
	//namedWindow("���", WINDOW_FREERATIO); 
	//�����Խ��ͼ��Խģ��  ����Size�Ĵ��뻹���Խ���ˮƽ������Size(15, 1)����ֱ������Size(1,15
	blur(image, dst, Size(15, 15), Point(-1, -1));
	imshow("���", dst);
}
//�����˹ģ��
void QuickDemo::gaussian_blur_demo(Mat &image)
{
	Mat dst;
	//����˵Ĵ�С��ע��һ��Ҫ�ǻ��� ż�����Ǵ����(Υ���˸�˹���Ļ���ԭ��)
	//sigma  ����������Size(0,0)��ʱ��opencv�ͻ��sigma���㴰�ڴ�С��
	//�����ڴ�С�Ѿ��趨һ��ֵ֮����ôsigma���������ʲô��û��Ч��������Ӵ��ڼ���õ�sigma��
	//���Ҵ��ڻ���sigma����ֵԽ��ͼ��Խģ����sigma��ͼ�ε�ģ��Ч�������������Ժܶ�ʱ�򶼻�����size����ֱ�����sigma�����鿴ģ��Ч��
	GaussianBlur(image, dst, Size(5, 5), 15);
	imshow("��˹ģ��", dst);
}
//����˫�߸�˹���
void QuickDemo::Bilateralgaussian_blur_demo(Mat &image)
{
	Mat dst;
	//100��ʾɫ�ʵľ���� Ҫ��һ��
	//10��ʾ�ռ����ľ����
	bilateralFilter(image, dst, 0, 100, 10);
	imshow("��˹ģ��", dst);
}

//����ʶ���demo
void QuickDemo::face_detection_demo()
{
	std::string rootdir = "D:/opencv4.4/opencv/sources/samples/dnn/face_detector/";
	//��ȡdnn�����Tensorflowģ��  ����һ�������ļ�
	cv::dnn::Net net = cv::dnn::readNetFromTensorflow(rootdir+"opencv_face_detector_uint8.pb", rootdir + "opencv_face_detector.pbtxt");
	VideoCapture capture(0);
	Mat frameVedio;
	while (true)
	{
		capture.read(frameVedio);
		if (frameVedio.empty())
			break;
		//ģ����Ҫ�Ĵ�С ��ֵ ���� ���Բ鿴dnn�µ�models.yml�ļ� 
		Mat blob = cv::dnn::blobFromImage(frameVedio, 1.0, Size(300, 300), Scalar(104, 177, 123), false, false);//��ȡģ��
		net.setInput(blob);//׼������   blob����NCWH (���ٸ���ͨ���������)
		Mat probs = net.forward();//�������    �����Ľ���Ƕ�����ͼ���и����imageindex���ڼ������εģ��ж��ٸ���ÿ���������С�
		Mat detectionMat(probs.size[2], probs.size[3], CV_32F, probs.ptr<float>());//���ߣ��������ͣ����ݵ�ַ
		//�������  
		for (int i = 0; i < detectionMat.rows; i++)
		{
			//ȡֵ�߸�ֵ 0���� 1�Լ���index  2�Լ��ĵ÷ֵ÷�Խ��Խ����������  34 ���Ͻǵ������  56���½ǵ������
			float confidence = detectionMat.at<float>(i, 2);
			if (confidence > 0.5)//����0.5�Ϳ�������������
			{
				//��ΪԤ�����������0-1֮��ģ�Ҫ����ʵ����� ��������������ֵ
				int x1 = static_cast<int>(detectionMat.at<float>(i, 3)*frameVedio.cols);
				int y1 = static_cast<int>(detectionMat.at<float>(i, 4)*frameVedio.rows);
				int x2 = static_cast<int>(detectionMat.at<float>(i, 5)*frameVedio.cols);
				int y2 = static_cast<int>(detectionMat.at<float>(i, 6)*frameVedio.rows);
				Rect rect(x1, y1, x2-x1, y2-y1);
				rectangle(frameVedio, rect, Scalar(0, 0, 255), 2, 8, 0);
			}
		}
		imshow("���������ʾ", frameVedio);
		int c = waitKey(10);
		if (c == 27)
			break;
	}

	capture.release();//����ͷ��Դ��Ҫ�ͷ�
}

//��Ƶ�̲��и���滻
void QuickDemo::beijing_tihuan_demo()
{
	VideoCapture captureCamear("D:/01.mp4");
	//get��Ƶ���� ע��Ҳ�ǿ���set���õ� ����ע�����������ͷ�Ļ���Ӳ���Ƿ�֧��set�Ĳ���
	int frame_width = captureCamear.get(CAP_PROP_FRAME_WIDTH);
	int frame_height = captureCamear.get(CAP_PROP_FRAME_HEIGHT);
	int frame_counts = captureCamear.get(CAP_PROP_FRAME_COUNT);
	int fps = captureCamear.get(CAP_PROP_FPS);
	std::cout << "frame_width = " << frame_width << std::endl;
	std::cout << "frame_height = " << frame_height << std::endl;
	std::cout << "frame_counts = " << frame_counts << std::endl;
	std::cout << "fps = " << fps << std::endl;

	//CAP_PROP_FOURCC  ��ȡԭ���ı�������   ע��size�Ĵ�С���ܱ�
	VideoWriter writer("D:/test.mp4", captureCamear.get(CAP_PROP_FOURCC), fps, Size(frame_width, frame_height), true);
	VideoCapture Camerwriter("D:/lane.avi");
	Mat frameCamear;
	Mat frameVedio;
	while (true)
	{
		captureCamear.read(frameCamear);//��ȡ��Ƶ ÿһ֡ �Ӷ�������Ƶ���ǲ���ͼ����
		Camerwriter.read(frameVedio);
		Mat hsv;
		cvtColor(frameCamear, hsv, COLOR_BGR2HSV);
		Mat mask;
		inRange(hsv, Scalar(35, 43, 46), Scalar(77, 255, 255), mask);//����hsvͼ�� ������ɫ��Ϊ�ֽ�����hsv��ɫ��hsv�������ֵ
		//imshow("inRange mask", mask);//ֻ�кڰ�  ����ɫ�����1��ɫ �������0��ɫ
		resize(frameVedio, frameVedio, Size(frame_width, frame_height), 0, 0, INTER_LINEAR);
		bitwise_not(mask, mask);//ȡ�� �ڱ�� �ױ��   �����൱�ڰ���ɫ���ֱ��0��ɫ���˲��ֱ��1��ɫ
		frameCamear.copyTo(frameVedio, mask);
		writer.write(frameVedio);//д���ļ�
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
	captureCamear.release();//����ͷ��Դ��Ҫ�ͷ�
	writer.release();//��Ƶд�����Ҳ��Ҫ�ͷ���Դ
}

//�����˹ģ�����̲���ͼ�滻
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
			if (m == 255) { // ����
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
				// ��������
				b1 = *bgrow++;
				g1 = *bgrow++;
				r1 = *bgrow++;

				// Ŀ��ǰ������
				b2 = *current++;
				g2 = *current++;
				r2 = *current++;

				// ���Ȩ��
				wt = m / 255.0;

				// ���
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
			background_02.copyTo(background_01);//���������Ƶ������Ͼ���Ҫ���� ͼƬ���
		}
		cvtColor(frame, hsv, COLOR_BGR2HSV);
		inRange(hsv, Scalar(35, 43, 46), Scalar(155, 255, 255), mask);

		// ��̬ѧ��ʴ����
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
