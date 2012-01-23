/*
 * rechthoek.cpp
 *
 *  Created on: Nov 25, 2011
 *      Author: stephan
 */
#include "library.h"
#include "gui.h"
using namespace std;
int main() {

  video_resource video(0);
  image_resource detection_img;
  window2D window;

  vector<vector< cv::Point> > buffer;
  while(1) {
    buffer = findSquares(video);
    detection_img = drawSquares(video,buffer);
    window.addToDraw(detection_img);
    window.Display();
  }
  return 0;
}
