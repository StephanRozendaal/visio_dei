/*
 * algorithms.h
 *
 *  Created on: Nov 25, 2011
 *      Author: stephan
 */

#ifndef ALGORITHMS_H_
#define ALGORITHMS_H_

namespace alg {
image_resource change_color_space(const image_resource, int);
namespace segmentation {
image_resource threshold(const image_resource, double, double, int);
}
namespace detection {
double angle(cv::Point, cv::Point, cv::Point);
void findSquares(const cv::Mat&, std::vector<std::vector<cv::Point> >&);
void drawSquares(cv::Mat&, std::vector<std::vector<cv::Point> >&);
}
}
#endif /* ALGORITHMS_H_ */
