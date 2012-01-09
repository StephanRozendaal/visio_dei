/*
 * algorithms.h
 *
 *  Created on: Nov 25, 2011
 *      Author: stephan
 */

#ifndef ALGORITHMS_H_
#define ALGORITHMS_H_

namespace alg
{
  /**
   * image_resource change_color_space(const image_resource&, const int)
   * verander de color space van een image_resource.
   * image_resource:    input image
   * int:               threshold type
   * return:            image_resource object.
   **/
  image_resource change_color_space(const image_resource&, const int);
  namespace segmentation
  {
    /**
     * image_resource threshold(image_resource input, double threshold, double max, int type)
     * voer een thresholding operatie uit op een image_resource.
     * input:       input image
     * threshold:   minimale threshold waarde
     * max:         maximale threshold waarde
     * type:        enumerated threshold type
     * return:      thresholded image object.
     **/
    image_resource threshold(const image_resource&, const double, const double, const int);
  }
  namespace detection
  {
    /**
     * angle(Point 1, Point 2, Point 0)
     * berekent de hoek die tussen 3 punten ligt.
     * Point 1,2,3: 3 CV punten.
     * return:      double waarde graden van de hoek.
     **/
    double angle(cv::Point, cv::Point, cv::Point);

    /**
     * vector >> vector<Point> findSquares(image_resource input_image&)
     * zoekt in de image_resource naar vierkanten
     * input_image&:    image_resource waarin vierkanten gezocht worden.
     * return:          vector van puntenvectoren.
     **/
    std::vector<std::vector<cv::Point> > findSquares(const image_resource&);

    /**
     * image_resource drawSquares(image_resource input_image&, vector<vector<Point> >&)
     * tekent rechthoeken
     * input_image&:    input image waarin rechthoeken in worden getekend.
     * vector->vector:  puntvectoren
     * return: input image waarin de rechthoeken zijn getekend.
     **/
    image_resource drawSquares(const image_resource&, const std::vector<std::vector<cv::Point> >&);

    calibrationParameters calibrateCamera(const int n_boards, const int board_w, const int board_h, const video_resource& cam); 
    void findChessboard();
  }
}
#endif /* ALGORITHMS_H_ */
