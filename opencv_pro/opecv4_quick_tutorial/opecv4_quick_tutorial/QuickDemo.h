#pragma once
#include<opencv2/opencv.hpp>
using namespace cv;//opencv�������ռ�
class QuickDemo
{
public:
	void colorSpace_Demo(Mat &image);//ʵ��BGRת�ҶȺ�hsv
	void mat_creat_Demo(Mat &image);//Mat�Ĵ��� clone   copyTo   zeros   ones  Scalar  =
	void pixel_visit_demo(Mat &image);//��ͼ�����صĶ�д����
	void opreat_demo(Mat &image);//Mat���������� �Ӽ��˳�����Ӧ��API
	void tracking_bar_demo(Mat &image);//������ʵ�����ȺͶԱȶȵĵ���
	void key_demo(Mat &image);//���ռ����¼�
	void color_style_demo(Mat &image);//ʵ��ͼ��ɫ�ʱ仯
	void bitwise_demo(Mat &image);//��Matʵ�����ص�λ����
	void channels_demo(Mat &image);//ͼ��ͨ���ķ���ϲ�
	void inrange_demo(Mat &image);//ɫ�ʿռ��ת��
	void pixel_statistic_demmo(Mat &image);//��������ֵͳ��
	void drawing_demo(Mat &image);//������״����
	void randomdrawing_demo(Mat &image);//��������漴����
	void polylinedrawing_demo(Mat &image);//���ƶ����
	void setMouseCallback_demo(Mat &image);//����������Ӧ
	void norm_demo(Mat &image);//��������ת������һ������
	void resize_demo(Mat &image);//ͼ���������ֵ
	void flip_demo(Mat &image);//��ת
	void rotate_demo(Mat &image);//��ת
	void video_demo(Mat &image);//��Ƶ��ȡ
	void histogram(Mat &image);//��ȡֱ��ͼ
	void histogram_2d_demo(Mat &image);//��ȡ��άֱ��ͼ
	void histogram_eq_demo(Mat &image);//��ȡֱ��ͼ�ľ��⻯
	void histogram_compare_demo();//��ֱ��ͼ���бȽ�
	void histogram_eqRGB_demo(Mat &image);//�Բ�ɫͼ�����ֱ��ͼ�ľ��⻯
	void blur_demo(Mat &image);//������
	void gaussian_blur_demo(Mat &image);//�����˹���
	void Bilateralgaussian_blur_demo(Mat &image);//����˫�߸�˹���
	void face_detection_demo();//����ʶ���demo
	void beijing_tihuan_demo();//��Ƶ�̲��и���滻
	void beijing_tihuan_demo1();//�����˹ģ�����̲���ͼ�滻

	QuickDemo();
	~QuickDemo();

private:
	
	
	
};

