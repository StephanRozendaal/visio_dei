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
	point_resource(const cv::Point&);
	~point_resource();
	void set_resource(const cv::Point&);
	cv::Point& get_resource();
protected:
	cv::Point point;
};

/**
 * basis CV Matrix image container klasse
 */
class image_resource {
public:
	image_resource();
	image_resource(const cv::Mat&);
	image_resource(const char* , const int);
	image_resource(const image_resource& other) : image(other.get_resource()), buffer(0) {}
	virtual ~image_resource();
	virtual void set_resource(const cv::Mat&);
	virtual cv::Mat& get_resource() const;
	virtual std::vector<unsigned char> to_sfml();
protected:
	cv::Mat image;
	std::vector<unsigned char> buffer;
};

/**
 * CV video container klasse
 * TODO: worden de frames goed opgehaald, testen met een videofile. Ook mogelijkheden om frame X op te vragen
 */
class video_resource : public image_resource {
public:
	video_resource(const int);
	video_resource(const char*);
	virtual ~video_resource();
	void set_resource(const int);
  void set_resource(const char*);
  cv::Mat& get_resource() const;
  std::vector<unsigned char> to_sfml();
protected:
  cv::VideoCapture video;
};

/**
 * Class CalibrationParameters
 * Constructor: () - leeg.
 * Constructor: (intrinsic_parameters, distortion_coeffs, hues, dhues, satval_l, satval_h)
 * void saveToFile(string filename) - slaat de parameters op in een XML file.
 * calibrationParameters fromFile(string filename) haalt parameters uit filename, geeft een parametersobject terug.
 */
class calibrationParameters {
  public:
    cv::Mat intrinsic_parameters;
    cv::Mat distortion_coeffs;

    calibrationParameters();
    calibrationParameters(cv::Mat ip, cv::Mat dc);

    void saveToFile(std::string filename);
    void fromFile(std::string filename);
};

#endif /* RESOURCE_H_ */
