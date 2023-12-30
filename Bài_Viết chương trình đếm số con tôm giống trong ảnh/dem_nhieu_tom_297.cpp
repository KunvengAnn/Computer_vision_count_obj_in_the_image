#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main() {
	//Read an image from the path
	Mat src = imread("tomgiong297.jfif");

	//convert the image to grayscale
	Mat gray;
	cvtColor(src, gray, COLOR_BGR2GRAY);

	//Apply GaussianBlur to reduce noise and smooth the image
	Mat blurred_image;
	GaussianBlur(gray, blurred_image, Size(5, 5),0);

	//Highlight edges using the laplacian method
	Mat edges;
	Laplacian(blurred_image, edges, CV_64F);

	//Convert negative values to positive
	edges = abs(edges);

	//Convert the value to 8-bit for display
	edges.convertTo(edges, CV_8U);

	//Threshold to create a binary image(black and white)
	Mat binary_image;
	threshold(edges, binary_image, 30, 255, THRESH_BINARY);
	imshow("binary image", binary_image);

	//FInd contours on the binary image
	vector<vector<Point>> contours;
	findContours(binary_image, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	//Draw contours on the original image for inspection
	Scalar color(0, 255, 0);
	drawContours(src, contours, -1, color,2);
	
	//show the number of contours, it representing the number of shrimp-like objects
	cout << "Number of the Shrimps is: " << contours.size() << endl;

	imshow("result", src);
	while(true)
		waitKey(0);
	return 0;
}