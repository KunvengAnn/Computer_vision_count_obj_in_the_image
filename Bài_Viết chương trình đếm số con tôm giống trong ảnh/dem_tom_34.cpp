#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main() {
	//read image from the path
	Mat src = imread("tomgiong3.jfif");

	//convert image to grayScale
	Mat gray;
	cvtColor(src, gray, COLOR_BGR2GRAY);

	//Apply GaussianBlur to reduce noise and smooth image
	Mat blurred_image;
	GaussianBlur(gray, blurred_image, Size(5, 5), 0);

	//Detect edges using Canny
	Mat edges;
	Canny(blurred_image, edges, 50, 70);
	imshow("Edges image by canny", edges);

	//Dilate to increases the size of detected edges
	Mat dilated;
	dilate(edges, dilated, Mat(), Point(-1, -1), 2);
	imshow("image dilated", dilated);

	//Find contours in the dilated image
	vector<vector<Point>> contours;
	findContours(dilated, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	//Draw contours on the original image
	drawContours(src, contours, -1, Scalar(0, 255, 0), 1);

	//Count the number of shrimps 
	int num_shrimps = contours.size();
	cout << "Number of Shrimps is: " << num_shrimps << endl;

	imshow("result", src);
	while(true)
		waitKey(0);
	return 0;
}