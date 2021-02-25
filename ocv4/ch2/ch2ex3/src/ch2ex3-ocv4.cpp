#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core/utility.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using std::cout;
using std::endl;
using std::string;
using std::vector;

int main(int argc, char **argv) {
    cv::Mat frame;
    cv::VideoCapture vcap;
    
    string keys = "{@cam|0|camera id}";
    cv::CommandLineParser parser(argc, argv, keys);
    int cam = parser.get<int>("@cam");
    
    if (argc <= 2) {
        vcap.open(cam);
    } else {
        cout << "Usage: " << argv[0] << " [CAMERA_ID]" << endl;
    }
    
    if (!vcap.isOpened()) {
        cout << "Could not open camera." << endl;
        return -1;
    }
    
    vcap >> frame;
    if (frame.empty()) {
        cout << "Got empty frame from camera, exiting." << endl;
        return -1;
    }
    
    char time_c_str[20];
    string filename;
    time_t raw_time;
    struct tm *now;
    
    raw_time = time(nullptr);
    now = localtime(&raw_time);
    
    strftime(time_c_str, 20, "%F-%H-%M-%S", now);
    
    filename = "capture-" + string(time_c_str) + ".png";
    
    // TODO: Should check if file exists, therefore allow multiple saves
    //  in one second
    
    cv::Mat frame_sdown;  // Scaled down frame
    cv::pyrDown(frame, frame_sdown);
    
    std::vector<int> png_params;
    png_params.push_back(cv::IMWRITE_PNG_COMPRESSION);
    png_params.push_back(3);
    
    bool success = false;
    try {
        success = cv::imwrite(filename, frame_sdown, png_params);
    } catch (const cv::Exception& ex) {
        cout << "An error ocurred during the conversion of the captured image"
            " to PNG." << endl;
    }
    
    if (success) {
        cout << "PNG image saved: " << filename << endl;
        
        return 0;
    } else {
        cout << "Couldn't write the image." << endl;
        
        return -1;
    }
    
    return -1;
}
