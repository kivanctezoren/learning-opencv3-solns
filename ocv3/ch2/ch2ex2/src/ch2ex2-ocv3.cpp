#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

int main(int argc, char **argv) {
    cv::namedWindow("ch2exp3-ocv3", cv::WINDOW_AUTOSIZE);
    cv::VideoCapture vcap;
    cv::Mat frame;
    
    // Note: The new string instance is not needed, argv[1] is a string and it
    //  is passed by const reference
    vcap.open(std::string(argv[1]));
    
    while (true) {
        vcap >> frame;
        
        if (frame.empty()) break;  // Reached end of video
        
        cv::imshow("ch2exp3-ocv3", frame);
        
        // If no keys pressed, waitKey returns -1. My system recognizes this as
        //  255, probably as a result of char overflow.
        int keycode = cv::waitKey(33) & 255;
        
        if (keycode) {
            keycode %= 255;  // Converting 255 to 0 & masking extraneous bits
        } else {  // Keycode 0 should break (?)
            std::cout << "Received keycode: " << keycode << " (" << (char) keycode << ") - Exiting." << std::endl;
            break;
        }
        
        if (keycode > 0) {  // if keycode was not -1 (or 255)
            std::cout << "Received keycode: " << keycode << " (" << (char) keycode << ") - Exiting." << std::endl;
            break;
        }
    }
    
    cv::destroyWindow("ch2exp3-ocv3");
    
    return 0;
}
