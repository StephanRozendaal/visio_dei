/*
 * =====================================================================================
 *
 *       Filename:  calibratie_schaakbord.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/17/2012 11:16:53 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include "library.h"

int main(int argc, char** argv) {

  video_resource cam(0);
  calibrationParameters par = calibrateCamera(10, 7, 5 , cam);
  par.saveToFile("calibration.xml");
  return 0;
}
