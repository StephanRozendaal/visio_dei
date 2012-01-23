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
point_resource::point_resource()
{

}

point_resource::point_resource(const cv::Point& p)
{
    this->point = p;
}

point_resource::~point_resource()
{
    //is misschien niet nodig, even kijken hoe dit gealloceerd word.
    //free this->point;
}

void point_resource::set_resource(const cv::Point& p)
{
    this->point = p;
}

cv::Point& point_resource::get_resource()
{
    return this->point;
}
/**
 * klasse image_source
 */
image_resource::image_resource()
{
    this->image = cv::Mat();
}
image_resource::image_resource(const cv::Mat& img)
{
    this->image = img;
}

image_resource::image_resource(const char* input, const int flags)
{
    this->image = cv::imread(input, flags);
}

image_resource::~image_resource()
{
    this->image.release();
}

void image_resource::set_resource(const cv::Mat& img)
{
    this->image = img;
}

cv::Mat& image_resource::get_resource() const
{
    return const_cast<cv::Mat&>(image);
}
std::vector<unsigned char> image_resource::to_sfml()
{
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
video_resource::video_resource(int input)
{
    video.open(input);
    video >> image;
}

video_resource::video_resource(const char* input)
{
    video.open(input);
    video >> image;
}

video_resource::~video_resource()
{
    video.release();
}

void video_resource::set_resource(int input)
{
    video.open(input);
}

void video_resource::set_resource(const char* input)
{
    video.open(input);
}

//TODO: exception throw declaratie als er geen videobeeld is.
cv::Mat& video_resource::get_resource() const
{
  cv::Mat temp_image;
  const_cast<cv::VideoCapture&>(this->video) >> const_cast<cv::Mat&>(this->image);
  return const_cast<cv::Mat&>(this->image);
}

std::vector<unsigned char> video_resource::to_sfml()
{
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

calibrationParameters::calibrationParameters() : 
  intrinsic_parameters(), 
  distortion_coeffs(),
  board_w(),
  board_h() 
{ }

calibrationParameters::calibrationParameters(const cv::Mat ip, const cv::Mat dc, const int board_w, const int board_h) : 
  intrinsic_parameters(ip), 
  distortion_coeffs(dc),
  board_w(board_w),
  board_h(board_h) 
{ }

void calibrationParameters::saveToFile(const std::string filename)
{
  try {
    cv::FileStorage fs(filename, cv::FileStorage::WRITE);
    fs << "intrinsic" << this->intrinsic_parameters;
    fs << "distortion" << this->distortion_coeffs;
    fs << "board_w" << this->board_w;
    fs << "board_h" << this->board_h;
    fs.release();
  } catch (cv::Exception& e) {
    throw std::runtime_error(e.what());
  }
}

void calibrationParameters::fromFile(const std::string filename)
{
  this->intrinsic_parameters = cv::Mat();
  this->distortion_coeffs = cv::Mat();
  this->board_w = 0, this->board_h = 0;
  try {
    cv::FileStorage fs(filename, cv::FileStorage::READ);
    fs["intrinsic"] >> this->intrinsic_parameters;
    fs["distortion"] >> this->distortion_coeffs;
    fs["board_w"] >> this->board_w;
    fs["board_h"] >> this->board_h;
    fs.release();
    // OpenCV silently ignores errors (like missing file to read),
    // so let's check that we got all parameters
    if (this->intrinsic_parameters.empty() || this->distortion_coeffs.empty())
      throw std::runtime_error("Missing calibration parameters in " + filename);
  } catch (cv::Exception& e) {
    throw std::runtime_error(e.what());
  }
}

