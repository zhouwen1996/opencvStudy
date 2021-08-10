#include "opencv2\core.hpp"
#include "opencv2\opencv.hpp"
using namespace cv;
int main()
{
	Mat image = imread("D:/catch.jpg");
	namedWindow("Mat test", WINDOW_FREERATIO);
	imshow("Mat test", image);

	waitKey(0);
	return 0;
}