//
// Created by Omri Carmi on 04/04/2018.
//

#ifndef VIDEOPROCESS_VIDEOPROCESS_H
#define VIDEOPROCESS_VIDEOPROCESS_H

#include <string>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

typedef struct VideoMeta_{
    int currentFrameNumber;
    double fps;
} VideoMeta;

class VideoProcess {

private:
    string mVideoSrc;
    VideoCapture mVideoCapture;
    int x;
public:
    VideoProcess(string videoSrc):mVideoSrc(videoSrc) {

        //open the video file for reading
        mVideoCapture.open(videoSrc);

        // if not success, exit program
        if (!mVideoCapture.isOpened())
        {
            throw "Cannot open the video file";
        }

    }

    void play(){

        // if not success, exit program
        if (!mVideoCapture.isOpened())
        {
            throw "Cannot open the video file";
        }

        //Uncomment the following line if you want to start the video in the middle
        //cap.set(CAP_PROP_POS_MSEC, 300);

        //get the frames rate of the video
        double fps = mVideoCapture.get(CAP_PROP_FPS);
        cout << "Frames per seconds : " << fps << endl;

        String window_name = "VideoWindow";

        namedWindow(window_name, WINDOW_NORMAL); //create a window

        while (true)
        {
            Mat frame;
            bool bSuccess = mVideoCapture.read(frame); // read a new frame from video

            //Breaking the while loop at the end of the video
            if (bSuccess == false)
            {
                cout << "Found the end of the video" << endl;
                break;
            }

            //show the frame in the created window
            imshow(window_name, frame);

            //wait for for 10 ms until any key is pressed.
            //If the 'Esc' key is pressed, break the while loop.
            //If the any other key is pressed, continue the loop
            //If any key is not pressed withing 10 ms, continue the loop
            if (waitKey(10) == 27)
            {
                cout << "Esc key is pressed by user. Stoppig the video" << endl;
                break;
            }
        }
    }

    void process(void(*handler)(Mat frame,VideoMeta meta)){
        // if not success, exit program
        if (!mVideoCapture.isOpened())
        {
            throw "Cannot open the video file";
        }

        VideoMeta meta;
        //Uncomment the following line if you want to start the video in the middle
        //cap.set(CAP_PROP_POS_MSEC, 300);

        //get the frames rate of the video
        double fps = mVideoCapture.get(CAP_PROP_FPS);
        cout << "Frames per seconds : " << fps << endl;

        meta.fps = fps;

        int currentFrameNumber = 0;
        while (true)
        {
            Mat frame;
            bool bSuccess = mVideoCapture.read(frame); // read a new frame from video

            //Breaking the while loop at the end of the video
            if (bSuccess == false)
            {
                cout << "Found the end of the video" << endl;
                break;
            }

            meta.currentFrameNumber = (++currentFrameNumber);

            //call the handler process function
            handler(frame,meta);
        }
    }

};


#endif //VIDEOPROCESS_VIDEOPROCESS_H
