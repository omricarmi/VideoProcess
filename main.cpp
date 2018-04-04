#include <iostream>
#include "VideoProcess.h"

using namespace std;

void processVideoExample(Mat frame,VideoMeta meta);

int main() {
    try {
        auto vp = VideoProcess("../videoDummy2.mp4");

//        vp.play(); // just play the video if you want

        vp.process(processVideoExample);

    }catch(...){
        cout << "video process failed" << endl;
    }
    return 0;
}

void processVideoExample(Mat frame,VideoMeta meta){

    cout << "START processing frame number: " << meta.currentFrameNumber<< endl;
    cout << "current FPS: " << meta.fps << endl;

    String window_name = "VideoWindow";

    namedWindow(window_name, WINDOW_NORMAL); //create a window

    //show the frame in the created window
    imshow(window_name, frame);
    waitKey(10);//this line can be commented is here just for the imshow to work properly
    //Example calc picture avg
    //https://docs.opencv.org/2.4/doc/user_guide/ug_mat.html
    const int numOfPixels = frame.cols*frame.rows;
    double sum = 0;
    for (int col = 0; col < frame.cols; ++col) {
        for (int row = 0; row < frame.rows; ++row) {
            Scalar intensity = frame.at<uchar>(row, col);
            sum += intensity.val[0];
        }
    }
    cout << "Mean of pixels is: " << sum/numOfPixels << endl;

    cout << "END processing frame number: " << meta.currentFrameNumber<< endl;
}