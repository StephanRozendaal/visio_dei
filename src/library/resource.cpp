/*
 * resource.cpp
 *
 *  Created on: Nov 24, 2011
 *      Author: stephan
 */
#include "library.h"

/**
 * klasse point_source
 */
point_resource::point_resource() {

}

point_resource::point_resource(cv::Point& p) {
	this->point = p;
}

point_resource::~point_resource() {
	//is misschien niet nodig, even kijken hoe dit gealloceerd word.
	//free this->point;
}

void point_resource::set_resource(cv::Point& p) {
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
image_resource::image_resource(cv::Mat& img) {
	this->image = img;
}

image_resource::image_resource(const char* input, int flags) {
	this->image = cv::imread(input, flags);
}

image_resource::~image_resource() {
	this->image.release();
}

void image_resource::set_resource(cv::Mat& img) {
	this->image = img;
}

cv::Mat* image_resource::get_resource() {
	return &image;
}
std::vector<unsigned char> image_resource::to_sfml() {
	std::vector<unsigned char> buffer;

	//voor encoderings instellingen
	std::vector<int> options;
	//vector wordt per set van 2 int waardes uitgelezen
	options.push_back(CV_IMWRITE_PNG_COMPRESSION); // naam of key
	options.push_back(2); //gewenste waarde

	cv::imencode(".png", image, buffer, options );
	return buffer;
}

/**
 * klasse video_source
 */
video_resource::video_resource(int input) {
	video.open(input);
	video >> image;
}

video_resource::video_resource(const char* input) {
	video.open(input);
	video >> image;
}

video_resource::~video_resource() {
	video.release();
}

void video_resource::set_resource(int input) {
	video.open(input);
}

void video_resource::set_resource(const char* input) {
	video.open(input);
}

cv::Mat* video_resource::get_resource() {
		video >> image;
		if(image.empty())
			return NULL;
		else
			return &image;
}

std::vector<unsigned char> video_resource::to_sfml() {
	this->get_resource();
	buffer.clear();
	//voor encoderings instellingen
	std::vector<int> options;
	//vector wordt per set van 2 int waardes uitgelezen
	options.push_back(CV_IMWRITE_PNG_COMPRESSION); // naam of key
	options.push_back(2); //gewenste waarde

	cv::imencode(".png", image, buffer, options );
	return buffer;
}
