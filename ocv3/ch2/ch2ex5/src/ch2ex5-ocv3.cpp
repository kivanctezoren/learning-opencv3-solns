#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core/utility.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <ctime>

#define DWNSMP_MIN 2

using std::cout;
using std::endl;
using std::string;
using std::vector;

void trackbar_slide(int pos, void *ds_lvl)
{
    /* Updates the downsampling level variable ds_lvl holds when trackbar is
     * adjusted. */
    
    *((int *) ds_lvl) = pos;
}

int main(int argc, char **argv) {
    cv::Mat frame;
    cv::VideoCapture vcap;
    
    string keys = "{@fps|60|captured frames per second}{@cam|0|camera id}";
    cv::CommandLineParser parser(argc, argv, keys);
    int cam = parser.get<int>("@cam");
    int wait_time = 1000 / parser.get<int>("@fps");
    
    if (argc <= 3) {
        vcap.open(cam);
    } else {
        cout << "Usage: " << argv[0] << " [FPS] [CAMERA_ID]" << endl;
    }
    
    if (!vcap.isOpened()) {
        cout << "Could not open camera." << endl;
        return -1;
    }
    
    cout << "Press Z to capture and save a downsampled color image." << endl;
    cout << "Press ESC to quit the program." << endl;
    
    cv::namedWindow("ch2ex5-ocv3", cv::WINDOW_NORMAL);
    
    int downsmp_lvl = DWNSMP_MIN;  // Between 2 and 8, for pyramid downsampling
    cv::createTrackbar("DownsampleLevel", "ch2ex5-ocv3", &downsmp_lvl, 8,
        trackbar_slide, &downsmp_lvl);
    cv::setTrackbarMin("DownsampleLevel", "ch2ex5-ocv3", downsmp_lvl);
    cv::setTrackbarPos("DownsampleLevel", "ch2ex5-ocv3", downsmp_lvl);
    
    while (true) {
        vcap >> frame;
        if (frame.empty()) {
            cout << "Got empty frame from camera, exiting." << endl;
            break;
        }
        
        for (int i = downsmp_lvl; i > DWNSMP_MIN; --i) {
            cv::pyrDown(frame, frame);
        }
        
        cv::imshow("ch2ex5-ocv3", frame);
        
        switch (cv::waitKey(wait_time)) {
        case 'z':
        case 'Z':
        {
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
            std::vector<int> png_params;
            png_params.push_back(cv::IMWRITE_PNG_COMPRESSION);
            png_params.push_back(3);
            
            bool success = false;
            try {
                success = cv::imwrite(filename, frame, png_params);
            } catch (const cv::Exception& ex) {
                cout << "An error ocurred during the conversion of the captured"
                    " image to PNG." << endl;
                // TODO: Should display the error in stderr
            }
            
            if (success) {
                cout << "PNG image saved with downsample level " << downsmp_lvl
                    << ": " << filename << endl;
            } else {
                cout << "Couldn't write the image." << endl;
            }
            
            break;
        }
        case 27:
            return 0;
        }
    }
    
    return -1;
}
