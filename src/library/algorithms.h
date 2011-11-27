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
void threshold(cv::Mat& input, cv::Mat& output, double thresh, double max, int type);
}

#endif /* ALGORITHMS_H_ */
