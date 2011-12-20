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
   * verander de color space van een image_resource.
   **/
  image_resource change_color_space(const image_resource, int);
  namespace segmentation
  {
    /**
     * threshold(image_resource input, double threshold, double max, int type)
     * voer een thresholding operatie uit op een image_resource
     **/
    void threshold(const image_resource, double, double, int);
  }
  namespace detection
  {
    /**
     * angle(Point 1, Point 2, Point 0)
     * berekent de hoek die tussen 3 punten ligt.
     **/
    double angle(cv::Point, cv::Point, cv::Point);

    /**
     * findSquares(image_resource input_image, vector<vector<Point> >)
     * zoekt in de image_resource naar vierkanten, geeft deze terug in een vector van puntenvectoren.
     **/
    void findSquares(image_resource, std::vector<std::vector<cv::Point> >&);
    /**
     * drawSquares(image_resource input_image, vector<vector<Point> >)
     * tekent rechthoeken, welke in het vector van puntvectoren staan in het input_image.
     **/
    void drawSquares(image_resource, std::vector<std::vector<cv::Point> >&);
    void calibrateCamera();
    void findChessboard();
  }
}
#endif /* ALGORITHMS_H_ */
