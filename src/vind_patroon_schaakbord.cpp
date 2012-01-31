#include "library.h"

int main(int argc, char** argv) {

  video_resource video(0);
  window3D mywindow;
  calibrationParameters calib;
  calib.fromFile("calibration.xml");
  cv::namedWindow("window");
  while(1) {
    findChessBoard(calib, video, mywindow);
  }
  return 0;
}
