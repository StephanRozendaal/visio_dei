/*
 * algorithms.h
 *
 *  Created on: Nov 25, 2011
 *      Author: stephan
 *
 * In deze file komen allemaal segmentatie functies.
 * 	- segmentatie door thresholding
 * 	- kleur segmentatie
 * 	- region growing
 * 	- segmentatie van regiogeometrische structuur
 */

#ifndef ALGORITHMS_H_
#define ALGORITHMS_H_

namespace alg {
image_resource change_color_space(image_resource input, int code);
namespace segmentation {
image_resource threshold(image_resource input, double thresh, double max, int type);
}
namespace detection {
double angle(cv::Point pt1, cv::Point pt2, cv::Point pt0);
void findSquares(const cv::Mat&, std::vector<std::vector<cv::Point> >&);
void drawSquares(cv::Mat&, std::vector<std::vector<cv::Point> >&);
}
}
#endif /* ALGORITHMS_H_ */
