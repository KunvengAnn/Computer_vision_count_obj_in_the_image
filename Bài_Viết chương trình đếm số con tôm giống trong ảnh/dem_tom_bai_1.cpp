#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main() {
    // Đọc ảnh từ đường dẫn
    Mat image = imread("D://images/tomgiong1.jfif");
    imshow("infinity image", image);

    // Chuyển đổi ảnh sang ảnh grayscale
    Mat gray;
    cvtColor(image, gray, COLOR_BGR2GRAY);

    // Áp dụng phép làm mờ để giảm nhiễu
    Mat blurred;
    GaussianBlur(gray, blurred, Size(9, 9), 0);

    // Áp dụng phép detect edges bằng phương pháp Canny
    Mat edges;
    Canny(blurred, edges,40, 70);
    imshow("image canny edges", edges);

    // Dilate để làm tăng kích thước các contour
    Mat dilated;
    dilate(edges, dilated, Mat(), Point(-1, -1), 1);
    imshow("dilated anh", dilated);

    // Tìm contours trong ảnh đã dilated
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(dilated, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    // Vẽ contours trên ảnh gốc để kiểm tra
    drawContours(image, contours, -1, Scalar(0, 255, 0), 1);
    imshow("image result", image);

    // Đếm số con tôm bằng cách đếm số contours
    int num_shrimps = contours.size();
    cout << "So luong tom la: " << num_shrimps << endl;

    while(true)
        waitKey(0);

    return 0;
}