#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main() {
    // Đọc ảnh từ đường dẫn
    //Images
    Mat src = imread("D://images//tomgiong1.jfif");
    if (!src.data) {
        cout << "not found path of images!"<<endl;
    }
   

    //Convert the iamge to grayscale
    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);

   //Apply a blur to reduce noise 
    Mat blurred;
    GaussianBlur(gray, blurred, Size(9, 9), 0);

    //Apply edge detection using the Canny method
    Mat edges;
    Canny(blurred, edges, 50, 70);

    //Dilate to increase the size of contours
    Mat dilated;
    dilate(edges, dilated, Mat(), Point(-1, -1), 1);

    //Find contours in the dilated image
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(dilated, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    //Draw contours on the original image for inspecton 
    Scalar color(0, 255, 0);
    drawContours(src, contours, -1, color, 1);

    //Count the number of Shrimps by counting the number of contours 
    int num_shrimps = contours.size();
    cout << "Number of Shrimps is : " << num_shrimps << endl;

    imshow("result", src);
    while(true)
        waitKey();
    return 0;
}