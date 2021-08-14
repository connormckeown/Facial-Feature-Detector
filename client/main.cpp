#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/imgproc/imgproc.hpp>
// #include <opencv2/opencv.hpp>


int main(int argc, char *argv[]) {
    // load classifiers
    cv::CascadeClassifier faceCascade { "haarcascade_frontalface_default.xml" };
    cv::CascadeClassifier eyesCascade { "haarcascade_eye_tree_eyeglasses.xml" };
    cv::CascadeClassifier noseCascade { "haarcascade_mcs_nose.xml" };
    cv::CascadeClassifier mouthCascade { "haarcascade_mcs_mouth.xml" };

    // read in image and convert to grayscale
    std::string image_path = argv[1];
    cv::Mat inputImage { cv::imread(image_path, cv::IMREAD_COLOR) };
    cv::Mat inputImageGray;
    cvtColor(inputImage, inputImageGray, CV_BGR2GRAY);

    // find all faces in the image, then loop over each one and detect their facial features
    std::vector<cv::Rect> faces;
    faceCascade.detectMultiScale(inputImageGray, faces);
    for (size_t i = 0; i < faces.size(); i++) {
        cv::Point faceCenter { faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 };
        cv::Size halfFace { faces[i].width/2, faces[i].height/2 };
        cv::ellipse(inputImage, faceCenter, halfFace, 0, 0, 360, cv::Scalar(255, 0, 255), 2);
        cv::Mat faceROIGray { inputImageGray(faces[i]) };
        
        // find eyes
        std::vector<cv::Rect> eyes;
        eyesCascade.detectMultiScale(faceROIGray, eyes);
        for (size_t j = 0; j < eyes.size(); j++) {
            cv::Point eyeCenter { faces[i].x + eyes[j].x + eyes[j].width/2, 
                                faces[i].y + eyes[j].y + eyes[j].height/2 };
            int radius { cvRound((eyes[j].width + eyes[j].height) * 0.25) };
            cv::circle(inputImage, eyeCenter, radius, cv::Scalar(255, 0, 0), 2);
        }

        // find noses
        std::vector<cv::Rect> noses;
        noseCascade.detectMultiScale(faceROIGray, noses);
        for (size_t j = 0; j < noses.size(); j++) {
            cv::Point noseCenter { faces[i].x + noses[j].x + noses[j].width/2, 
                                faces[i].y + noses[j].y + noses[j].height/2 };
            int radius { cvRound((noses[j].width + noses[j].height) * 0.25) };
            cv::circle(inputImage, noseCenter, radius, cv::Scalar(0, 0, 255), 2);
        }

        
        // find mouths
        std::vector<cv::Rect> mouths;
        mouthCascade.detectMultiScale(faceROIGray, mouths);
        for (size_t j = 0; j < mouths.size(); j++) {
            cv::Point mouthCenter { faces[i].x + mouths[j].x + mouths[j].width/2, 
                                faces[i].y + mouths[j].y + mouths[j].height/2 };
            int radius { cvRound((mouths[j].width + mouths[j].height) * 0.25) };

            // only draw mouth if its below the nose
            for (size_t k = 0; k < noses.size(); k++) {
                if (noses[k].y + noses[k].height < mouths[j].y + mouths[j].height/2) {
                    cv::circle(inputImage, mouthCenter, radius, cv::Scalar(0, 255, 0), 2);
                }
            }
        }
        
    }

    // write image to file
    cv::imwrite("pred.jpg", inputImage);

    return 0;
}