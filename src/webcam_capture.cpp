
//opencv
#include "opencv2/opencv.hpp"
#include "cv.h"
#include "highgui.h"

//std
#include <iostream>
#include <cstdlib>

//main
int main(int argc, char *argv[])
{
    cv::VideoCapture camera; //OpenCV video capture object
    cv::Mat image; //OpenCV image object
	int cam_id; //camera id . Associated to device number in /dev/videoX
	cv::Scalar_<unsigned char> px_value; //pixel value (4-element vector)
	int user_key; //user pressed key to quit

	//check user args
	switch(argc)
	{
		case 1: //no argument provided, so try /dev/video0
			cam_id = 0;
			break;
		case 2: //an argument is provided. Get it and set cam_id
			cam_id = atoi(argv[1]);
			break;
		default:
			std::cout << "Invalid number of arguments. Call program as: webcam_capture [video_device_id]. " << std::endl;
			std::cout << "EXIT program." << std::endl;
			break;
	}

	//advertising to the user
	std::cout << "Opening video device " << cam_id << std::endl;

    //open the video stream and make sure it's opened
    if( !camera.open(cam_id) )
	{
        std::cout << "Error opening the camera. May be invalid device id. EXIT program." << std::endl;
        return -1;
    }

    //capture loop. Out of user press a key
    while(1)
	{
		//Read image and check it. Blocking call up to a new image arrives from camera.
        if(!camera.read(image))
		{
            std::cout << "No frame" << std::endl;
            cv::waitKey();
        }
	// change the 8 neigbors of the central pixel to the color yellow

	
	std::cout <<"the value of the central pixel is:" << (image.rows/2) << ":" << (image.cols/2) << std::endl;//show central pixel value
	
			
	for(int x =319; x < 322; x++)
		{
		for(int y = 239; y < 241; y ++){
			image.at<cv::Vec3b>(y,x)[0] = 0;  
			image.at<cv::Vec3b>(y,x)[1] = 255;  
			image.at<cv::Vec3b>(y,x)[2] = 255;}
		}
	std::cout <<"Color" <<image.at<cv::Vec3b>(240,320)[0] <<","<< image.at<cv::Vec3b>(240,320)[1]<<","<< image.at<cv::Vec3b>(240,320)[2]<< std::endl;
        //show image in a window
        cv::imshow("Output Window", image);
	std::cout << "image size is: " << image.rows << "x" << image.cols << std::endl;

		//Waits 30 millisecond to check if 'q' key has been pressed. If so, breaks the loop. Otherwise continues.
    	if( (unsigned char)(cv::waitKey(30) & 0xff) == 'q' ) break; 
    }
}
