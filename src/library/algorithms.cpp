/*
 * algorithms.cpp
 *
 *  Created on: Nov 25, 2011
 *      Author: stephan
 */

#include "library.h"

namespace alg {
image_resource change_color_space(image_resource input, int code) {
	using namespace cv;
	Mat output;
	Mat *temp = input.get_resource();
	Mat image(*temp);
	cvtColor(image, output, code);
	image_resource *img_output = new image_resource(output);
	return *img_output;
}
namespace segmentation {

image_resource threshold(image_resource input, double thresh, double max,
		int type) {
	using namespace cv;
	Mat output;
	Mat *temp = input.get_resource();
	Mat image(*temp);
	threshold(image, output, thresh, max, type);
	image_resource *img_output = new image_resource(output);
	return *img_output;
}
}
namespace detection {

/**
 * angle() is een hulpfunctie voor findSquares()
 */
double angle(cv::Point pt1, cv::Point pt2, cv::Point pt0) {
	double dx1 = pt1.x - pt0.x;
	double dy1 = pt1.y - pt0.y;
	double dx2 = pt2.x - pt0.x;
	double dy2 = pt2.y - pt0.y;
	return (dx1 * dx2 + dy1 * dy2)
			/ sqrt((dx1 * dx1 + dy1 * dy1) * (dx2 * dx2 + dy2 * dy2) + 1e-10);
}

/**
 * gepikt uit de CV samples
 *
 */
void findSquares(image_resource image_res,
		std::vector<std::vector<cv::Point> >& squares) {
	using namespace std;
	using namespace cv;

	//image resource omzetten
	Mat *temp = image_res.get_resource();
	Mat image(*temp);

	//waardes voor threshold levels
	int thresh = 50, N = 11;
	squares.clear();

	Mat pyr, timg, gray0(image.size(), CV_8U), gray;

	// down-scale and upscale the image to filter out the noise
	pyrDown(image, pyr, Size(image.cols / 2, image.rows / 2));
	pyrUp(pyr, timg, image.size());
	vector<vector<Point> > contours;

	// find squares in every color plane of the image
	for (int c = 0; c < 3; c++) {
		int ch[] = { c, 0 };
		mixChannels(&timg, 1, &gray0, 1, ch, 1);

		// try several threshold levels
		for (int l = 0; l < N; l++) {
			// hack: use Canny instead of zero threshold level.
			// Canny helps to catch squares with gradient shading
			if (l == 0) {
				// apply Canny. Take the upper threshold from slider
				// and set the lower to 0 (which forces edges merging)
				Canny(gray0, gray, 0, thresh, 5);
				// dilate canny output to remove potential
				// holes between edge segments
				dilate(gray, gray, Mat(), Point(-1, -1));
			} else {
				// apply threshold if l!=0:
				//     tgray(x,y) = gray(x,y) < (l+1)*255/N ? 255 : 0
				gray = gray0 >= (l + 1) * 255 / N;
			}

			// find contours and store them all as a list
			findContours(gray, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);

			vector<Point> approx;

			// test each contour
			for (size_t i = 0; i < contours.size(); i++) {
				// approximate contour with accuracy proportional
				// to the contour perimeter
				approxPolyDP(Mat(contours[i]), approx,
						arcLength(Mat(contours[i]), true) * 0.02, true);

				// square contours should have 4 vertices after approximation
				// relatively large area (to filter out noisy contours)
				// and be convex.
				// Note: absolute value of an area is used because
				// area may be positive or negative - in accordance with the
				// contour orientation
				if (approx.size() == 4 && fabs(contourArea(Mat(approx))) > 1000
						&& isContourConvex(Mat(approx))) {
					double maxCosine = 0;

					for (int j = 2; j < 5; j++) {
						// find the maximum cosine of the angle between joint edges
						double cosine = fabs(
								angle(approx[j % 4], approx[j - 2],
										approx[j - 1]));
						maxCosine = MAX(maxCosine, cosine);
					}

					// if cosines of all angles are small
					// (all angles are ~90 degree) then write quandrange
					// vertices to resultant sequence
					if (maxCosine < 0.3)
						squares.push_back(approx);
				}
			}
		}
	}
}
}

/**
 * tekent de rechthoeken op het image uit de parameter
 */
void drawSquares(cv::Mat& image,
	std::vector<std::vector<cv::Point> >& squares) {
using namespace cv;
for (size_t i = 0; i < squares.size(); i++) {
	const Point* p = &squares[i][0];
	int n = (int) squares[i].size();
	polylines(image, &p, &n, 1, true, Scalar(0, 255, 0), 3, CV_AA);
}
// kleine aanpassing voor webcam die erg kleine beelden geeft, 320x200 resolutie
resize(image, image, Size(), 3.0, 3.0, INTER_LINEAR);
}
}

