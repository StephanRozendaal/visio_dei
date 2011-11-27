/*
 * algorithms.cpp
 *
 *  Created on: Nov 25, 2011
 *      Author: stephan
 */

#include "library.h"

namespace alg {
void threshold(cv::Mat& input, cv::Mat& output, double thresh, double max,
		int type) {
	cv::threshold(input, output, thresh, max, type);
}
}


