#include <iostream>
#include "VideoProcess.h"

using namespace std;

void processVideoExample(Mat frame,VideoMeta meta);

int main() {
    try {
        // 1: create VideoProcess Instance with the location of the video.
        // best idea is to write the full  path to it.
        auto vp = VideoProcess("../videoDummy2.mp4");

//        vp.play(); // just play the video if you want

        // 2: call the process method and
        // pass to it the name of function that going to handle each frame
        vp.process(processVideoExample);

    }catch(...){
        cout << "video process failed" << endl;
    }
    return 0;
}

// 3: you need to define function with this signature.
// the name isn't must be as below as long as you give the same name to vp.process()
void processVideoExample(Mat frame,VideoMeta meta){

    cout << "START processing frame number: " << meta.currentFrameNumber<< endl;
    cout << "current FPS: " << meta.fps << endl;

    String window_name = "VideoWindow";

    namedWindow(window_name, WINDOW_NORMAL); //create a window

    //show the frame in the created window
    imshow(window_name, frame);
    waitKey(10);//this line can be commented is here just for the imshow to work properly
    //Example calc picture avg
    //for more info --->> https://docs.opencv.org/2.4/doc/user_guide/ug_mat.html
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
