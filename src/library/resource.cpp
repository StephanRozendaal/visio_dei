/*
 * resource.cpp
 *
 *  Created on: Nov 24, 2011
 *      Author: stephan
 */
#include "library.h"

/**
 * point klasse point_source
 */
point_resource::point_resource() {

}

point_resource::point_resource(cv::Point p) {
	this->point = p;
}

point_resource::~point_resource() {
	//is misschien niet nodig, even kijken hoe dit gealloceerd word.
	//free this->point;
}

void point_resource::set_resource(cv::Point p) {
	this->point = p;
}

cv::Point* point_resource::get_resource() {
	return &this->point;
}
/**
 * klasse image_source
 */
image_resource::image_resource() {

}
image_resource::image_resource(const cv::Mat img) {
	this->image = img;
}

image_resource::image_resource(const char* input, int flags) {
	this->image = cv::imread(input, flags);
}

image_resource::~image_resource() {
	this->image.release();
}

void image_resource::set_resource(const cv::Mat img) {
	this->image = img;
}

cv::Mat* image_resource::get_resource() {
	return &image;
}

/**
 * klasse video_source
 */
video_resource::video_resource(int input) {
	video.open(input);
}

video_resource::video_resource(const char input) {
	video.open(input);
}

video_resource::~video_resource() {
	video.release();
}

void video_resource::set_resource(int input) {
	video.open(input);
}

void video_resource::set_resource(const char input) {
	video.open(input);
}

cv::Mat* video_resource::get_resource() {
		video >> image;
		if(image.empty())
			return NULL;
		else
			return &image;
}

