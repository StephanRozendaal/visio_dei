/*
 * =====================================================================================
 *
 *       Filename:  rechthoek.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/22/2011 11:25:28 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include "library.h"
#include "gui.h"
using namespace std;
int main() {

  video_resource video(0);
  window2D window;

  vector<vector< cv::Point> > buffer;
  while(1) {
    alg::detection::findSquares(video, buffer);
    alg::detection::drawSquares(video,buffer);
    window.addToDraw(video);
    window.Display();
  }
  return 0;
}
