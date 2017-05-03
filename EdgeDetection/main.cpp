#include <opencv2\opencv.hpp>
#include <cmath>
#include <cstdio>

using namespace cv;
using namespace std;

float pi = 3.1415926535897;

int main() {
	int imScale = 8;
	Mat image, imageGaussian, imageX, imageY, imageG, imageT, imageS;
	
	image = imread("Image 1.jpg", CV_LOAD_IMAGE_GRAYSCALE);

	imageGaussian = Mat(image.rows, image.cols, CV_32F);
	imageX = Mat(image.rows, image.cols, CV_32F);
	imageY = Mat(image.rows, image.cols, CV_32F);
	imageG = Mat(image.rows, image.cols, CV_32F);
	imageT = Mat(image.rows, image.cols, CV_32F);
	imageS = Mat(image.rows, image.cols, CV_32F);

	GaussianBlur(image, imageGaussian, Size(5, 5), 0, 0);
	imageGaussian.convertTo(imageGaussian, CV_32F);
	Sobel(imageGaussian, imageX, -1, 1, 0, 5);
	Sobel(imageGaussian, imageY, -1, 0, 1, 5);

	imageX.convertTo(imageX, CV_32F);
	imageY.convertTo(imageY, CV_32F);
	imageG.convertTo(imageG, CV_32F);
	imageT.convertTo(imageT, CV_32F);
	imageS.convertTo(imageS, CV_32F);

	int x = 0;
	int y = 0;
	for (y = 0; y < imageX.rows; y++) {
		for (x = 0; x < imageX.cols; x++) {
			float gx = imageX.at<float>(y, x);
			float gy = imageY.at<float>(y, x);
			imageG.at<float>(y, x) = sqrt(pow(gx, 2) + pow(gy, 2));
			float ang = atan2(gy, gx) * 360 / (2 * pi) + 180;
			imageT.at<float>(y, x) = ang;
		}
	}
	for (y = 1; y < imageG.rows - 1; y++) {
		for (x = 1; x < imageG.cols - 1; x++) {
			float g = imageG.at<float>(y, x);
			float t = imageT.at<float>(y, x);
			float i = g;
			if (g > 0) {
				if ((((t <= 22.5)) || ((t > 337.5))) || ((t > 157.5) && (t <= 202.5))) {
					if ((g >= imageG.at<float>(y, x - 1)) || (g >= imageG.at<float>(y, x + 1))) {
						imageS.at<float>(y, x) = i;
					}
					else {
						imageS.at<float>(y, x) = 0;
					}
				}
				else if (((t > 22.5) && (t <= 67.5)) || ((t > 202.5) && (t <= 247.5))) {
					if ((g >= imageG.at<float>(y - 1, x + 1)) || (g >= imageG.at<float>(y + 1, x - 1))) {
						imageS.at<float>(y, x) = i;
					}
					else {
						imageS.at<float>(y, x) = 0;
					}
				}
				else if (((t > 67.5) && (t <= 112.5)) || ((t > 247.5) && (t <= 292.5))) {
					if ((g >= imageG.at<float>(y - 1, x)) || (g >= imageG.at<float>(y + 1, x))) {
						imageS.at<float>(y, x) = i;
					}
					else {
						imageS.at<float>(y, x) = 0;
					}
				}
				else if (((t > 112.5) && (t <= 157.5)) || ((t > 292.5) && (t <= 337.5))) {
					if ((g >= imageG.at<float>(y - 1, x - 1)) || (g >= imageG.at<float>(y + 1, x + 1))) {
						imageS.at<float>(y, x) = i;
					}
					else {
						imageS.at<float>(y, x) = 0;
					}
				}
			}
		}
	}
	imwrite("imageGrey.jpg", image);
	imwrite("imageGaus.jpg", imageGaussian);
	imwrite("imageX.jpg", imageX);
	imwrite("imageY.jpg", imageY);
	imwrite("imageG.jpg", imageG);
	imwrite("imageT.jpg", imageT);
	imwrite("imageS.jpg", imageS);
	return 0;
}