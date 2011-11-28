/*
 * resource.h
 *
 *  Created on: Nov 24, 2011
 *      Author: stephan
 */

#ifndef RESOURCE_H_
#define RESOURCE_H_

/**
 * basis cv Point container klasse
 * TODO: verschillende point typen
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

/**
 * basis CV Matrix image container klasse
 */
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

/**
 * CV video container klasse
 * TODO: worden de frames goed opgehaald, testen met een videofile. Ook mogelijkheden om frame X op te vragen
 */
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
