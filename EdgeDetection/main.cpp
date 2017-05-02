#include <opencv2\opencv.hpp>
#include <cmath>

using namespace cv;
using namespace std;

int main() {
	double pi = 3.1415926535897;
	int imScale = 5;
	Mat image;
	Mat imageGrey;
	Mat imageGaussian;
	Mat imageX;
	Mat imageY;
	Mat imageG;
	Mat imageT;
	Mat kernelGaussian = (Mat_<double>(3, 3) << 1, 2, 1, 2, 4, 2, 1, 2, 1) / 16;
	Mat kernelX = (Mat_<double>(3, 3) << -1, 0, 1, -2, 0, 2, -1, 0, 1);
	Mat kernelY = (Mat_<double>(3, 3) << -1, -2, -1, 0, 0, 0, 1, 2, 1);

	image = imread("Image 1.jpg", CV_LOAD_IMAGE_COLOR);
	resize(image, image, Size(image.cols / imScale, image.rows / imScale));
	cvtColor(image, imageGrey, COLOR_BGR2GRAY);
	filter2D(imageGrey, imageGaussian, -1, kernelGaussian, Point(-1, -1), 0);
	filter2D(imageGaussian, imageX, -1, kernelX, Point(-1, -1), 0);
	filter2D(imageGaussian, imageY, -1, kernelY, Point(-1, -1), 0);
	int x = 0;
	int y = 0;
	imageG = imageGrey.clone();
	imageT = imageGrey.clone();
	for (y = 0; y < imageG.rows; y++) {
		for (x = 0; x < imageG.cols; x++) {
			int gx = imageX.at<uchar>(y, x);
			int gy = imageY.at<uchar>(y, x);
			imageG.at<uchar>(y, x) = sqrt(pow(gx, 2) + pow(gy, 2)); 
			float ang = atan2(gy, gx) * 360 / (2 * pi);
			imageT.at<uchar>(y, x) = ang;
		}
	}


	/*namedWindow("Input", WINDOW_AUTOSIZE);
	namedWindow("Grey", WINDOW_AUTOSIZE);
	namedWindow("Gaussian", WINDOW_AUTOSIZE);
	namedWindow("Gx", WINDOW_AUTOSIZE);
	namedWindow("Gy", WINDOW_AUTOSIZE);*/
	namedWindow("G", WINDOW_AUTOSIZE);
	namedWindow("T", WINDOW_AUTOSIZE);
	
	/*if (!image.empty()) {
		imshow("Input", image);
	}
	if (!imageGrey.empty()) {
		imshow("Grey", imageGrey);
	}
	if (!imageGaussian.empty()) {
		imshow("Gaussian", imageGaussian);
	}
	if (!imageX.empty()) {
		imshow("Gx", imageX);
	}
	if (!imageY.empty()) {
		imshow("Gy", imageY);
	}*/
	if (!imageG.empty()) {
		imshow("G", imageG);
	}
	if (!imageT.empty()) {
		imshow("T", imageT);
	}

	waitKey(0);
	destroyAllWindows();

	return 0;
}