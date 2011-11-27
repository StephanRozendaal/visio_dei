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
class point_resource {
public:
	point_resource();
	point_resource(cv::Point&);
	~point_resource();
	void set_resource(cv::Point&);
	cv::Point* get_resource();
protected:
	cv::Point point;
};
class image_resource {
public:
	image_resource();
	image_resource(cv::Mat&);
	image_resource(const char* , int);
	~image_resource();
	void set_resource(cv::Mat&);
	cv::Mat get_resource();
protected:
	cv::Mat image;
};

class video_resource : public image_resource {
public:
	video_resource(int);
	video_resource(const char*);
	~video_resource();
	void set_resource(int);
	void set_resource(const char*);
	cv::Mat* get_resource();
protected:
	cv::VideoCapture video;
};

#endif /* RESOURCE_H_ */
