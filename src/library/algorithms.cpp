/*
 * algorithms.cpp
 *
 *  Created on: Nov 25, 2011
 *      Author: stephan
 */

#include "library.h"

namespace alg {
image_resource threshold(image_resource input, double thresh, double max,
		int type) {
	cv::Mat output;
	cv::threshold(input.get_resource(), output, thresh, max, type);
	image_resource *img_output = new image_resource(output);
	return *img_output;
}
}

