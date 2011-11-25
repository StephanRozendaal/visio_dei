/*
 * main.cpp
 *
 *  Created on: Nov 18, 2011
 *      Author: stephan
 */
#include "lua/lua.h"
#include "library/library.h"

int main() {

	video_resource source(0);
	cv::Mat * image = source.get_resource();
	cv::namedWindow("scherm", CV_WINDOW_NORMAL);
	cv::imshow("scherm", *image);
	cv::imwrite("test.jpg", *image);
return 0;
}



