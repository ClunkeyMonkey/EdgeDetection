#include <opencv2\opencv.hpp>
#include <cmath>
#include <cstdio>

using namespace cv;
using namespace std;

float pi = 3.1415926535897;

float wT = 75;
float bT = 20;

void rabithole(Mat* img, int x, int y);

int main() {
	Mat image, imageGaussian, imageX, imageY, imageG, imageT, imageS, imageH, imageF;
	
	image = imread("Image 1.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	imageGaussian = Mat(image.rows, image.cols, CV_32F);
	imageX = Mat(image.rows, image.cols, CV_32F);
	imageY = Mat(image.rows, image.cols, CV_32F);
	imageG = Mat(image.rows, image.cols, CV_32F);
	imageT = Mat(image.rows, image.cols, CV_32F);
	imageS = Mat(image.rows, image.cols, CV_32F);
	imageH = Mat(image.rows, image.cols, CV_32F);
	imageF = Mat(image.rows, image.cols, CV_32F);

	GaussianBlur(image, imageGaussian, Size(3, 3), 0, 0);
	imageGaussian.convertTo(imageGaussian, CV_32F);
	Sobel(imageGaussian, imageX, CV_32F, 1, 0, 3);
	Sobel(imageGaussian, imageY, CV_32F, 0, 1, 3);

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
			if ((((t <= 22.5)) || ((t > 337.5))) || ((t > 157.5) && (t <= 202.5))) {
				if ((g > imageG.at<float>(y, x - 1)) && (g > imageG.at<float>(y, x + 1))) {
					imageS.at<float>(y, x) = g;
				} else {
					imageS.at<float>(y, x) = 0;
				}
			}
			else if (((t > 22.5) && (t <= 67.5)) || ((t > 202.5) && (t <= 247.5))) {
				if ((g > imageG.at<float>(y - 1, x + 1)) && (g > imageG.at<float>(y + 1, x - 1))) {
					imageS.at<float>(y, x) = g;
				} else {
					imageS.at<float>(y, x) = 0;
				}
			}
			else if (((t > 67.5) && (t <= 112.5)) || ((t > 247.5) && (t <= 292.5))) {
				if ((g > imageG.at<float>(y - 1, x)) && (g > imageG.at<float>(y + 1, x))) {
					imageS.at<float>(y, x) = g;
				} else {
					imageS.at<float>(y, x) = 0;
				}
			}
			else if (((t > 112.5) && (t <= 157.5)) || ((t > 292.5) && (t <= 337.5))) {
				if ((g > imageG.at<float>(y - 1, x - 1)) && (g > imageG.at<float>(y + 1, x + 1))) {
					imageS.at<float>(y, x) = g;
				} else {
					imageS.at<float>(y, x) = 0;
				}
			}
		}
	}
	imageH = imageS.clone();
	int i;
	for (y = 1; y < imageH.rows - 1; y++) {
		for (x = 1; x < imageH.cols - 1; x++) {
			float val = imageH.at<float>(y, x);
			if (val > wT) {
				imageH.at<float>(y, x) = 0xFFFF;
				rabithole(&imageH, y, x);
			}
		}
	}
	for (y = 1; y < imageH.rows - 1; y++) {
		for (x = 1; x < imageH.cols - 1; x++) {
			float val = imageH.at<float>(y, x);
			if (val == 0xFFFF) {
				imageF.at<float>(y, x) = 0xFFFF;
			}
		}
	}
	imwrite("image02_Grey.jpg", image);
	imwrite("image03_Gaussian.jpg", imageGaussian);
	imwrite("image04_XComponent.jpg", imageX);
	imwrite("image05_YComponent.jpg", imageY);
	imwrite("image06_Magnitude.jpg", imageG);
	imwrite("image07_Theta.jpg", imageT);
	imwrite("image08_Suppressed.jpg", imageS);
	imwrite("image09_Hysteresis.jpg", imageH);
	imwrite("image10_Final.jpg", imageF);
	return 0;
}

void rabithole(Mat* img, int y, int x) {
	img[0].at<float>(y, x) = 0xFFFF;
	if ((img[0].at<float>(y - 1, x - 1) > bT) && (img[0].at<float>(y - 1, x - 1) < wT)){
		rabithole(img, y - 1, x - 1);
	} else if ((img[0].at<float>(y - 1, x) > bT) && (img[0].at<float>(y - 1, x) < wT)) {
		rabithole(img, y - 1, x);
	} else if ((img[0].at<float>(y - 1, x + 1) > bT) && (img[0].at<float>(y - 1, x + 1) < wT)) {
		rabithole(img, y - 1, x + 1);
	} else if ((img[0].at<float>(y, x - 1) > bT) && (img[0].at<float>(y, x - 1) < wT)) {
		rabithole(img, y, x - 1);
	} else if ((img[0].at<float>(y, x + 1) > bT) && (img[0].at<float>(y, x + 1) < wT)) {
		rabithole(img, y, x + 1);
	} else if ((img[0].at<float>(y + 1, x - 1) > bT) && (img[0].at<float>(y + 1, x - 1) < wT)) {
		rabithole(img, y + 1, x - 1);
	} else if ((img[0].at<float>(y + 1, x) > bT) && (img[0].at<float>(y + 1, x) < wT)) {
		rabithole(img, y + 1, x);
	} else if ((img[0].at<float>(y + 1, x + 1) > bT) && (img[0].at<float>(y + 1, x + 1) < wT)) {
		rabithole(img, y + 1, x + 1);
	}
}