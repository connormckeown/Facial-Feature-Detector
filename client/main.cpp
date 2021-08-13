#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

int main(int argc, char *argv[]) {
    string image_path = argv[1];
    Mat img = imread(image_path, IMREAD_COLOR);

    if(img.empty()) {
        cout << "cpp: Could not read the image: " << image_path << endl;
        return 0;
    }
    cout << "cpp: Successfully read image" << endl;
}