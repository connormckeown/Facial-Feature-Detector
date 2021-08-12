#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

int main(int argc, char *argv[]) {
    cout << "Hello from cpp container" << endl;

    string image_path = "sample.jpg";
    Mat img = imread(image_path, IMREAD_COLOR);

    if(img.empty()) {
        cout << "cpp: Could not read the image: " << image_path << endl;
    }
    
}