/*
 * resource.cpp
 *
 *  Created on: Nov 24, 2011
 *      Author: stephan
 */
#include "library.h"

/**
 * klasse image_source
 */
image_source::image_source(cv::Mat* img) {
	this->image = img;
}

image_source::~image_source() {
	this->image.release();
}

void image_source::set_source(cv::Mat* img) {
	this->image = img;
}

cv::Mat* image_source::get_source() {
	return image;
}

/**
 * klasse video_source
 */
video_source::video_source(int input) {
	video.VideoCapture();
	video.open(input);
}

video_source::video_source(const char input) {
	video.VideoCapture();
	video.open(input);
}

video_source::~video_source() {
	video.release();
}

void video_source::set_source(int input) {
	video.open(input);
}

void video_source::set_source(const char input) {
	video.open(input);
}

cv::Mat* video_source::get_source() {
	cv::Mat temp;

	if (video.read(temp))
		return &temp;
	else
		return NULL;
}

