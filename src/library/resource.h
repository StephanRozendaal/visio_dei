/*
 * resource.h
 *
 *  Created on: Nov 24, 2011
 *      Author: stephan
 */

#ifndef RESOURCE_H_
#define RESOURCE_H_

#include "library.h"

/**
 * basis cv Matrix container klasse
 */
class image_source {
public:
	image_source();
	image_source(const cv::Mat img);
	image_source(const char* , int);
	~image_source();
	void set_source(const cv::Mat img);
	cv::Mat* get_source();
protected:
	cv::Mat image;
};

class video_source : public image_source {
public:
	video_source(int input);
	video_source(const char input);
	~video_source();
	void set_source(int input);
	void set_source(const char input);
	cv::Mat* get_source();
protected:
	cv::VideoCapture video;
};

#endif /* RESOURCE_H_ */
