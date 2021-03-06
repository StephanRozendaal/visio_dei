/*
 * window_3d.h
 *
 *  Created on: Dec 7, 2011
 *      Author: stephan

 * De window3D klasse, wordt gebruikt om een patroon in een 3D scherm te renderen
 * De constructor maakt een thread aan, waarin het renderen gebeurd.
 * met de funtie addObject wordt aangegeven waar het patroon zich bevindt.
 */

#ifndef WINDOW_3D_H_
#define WINDOW_3D_H_

class window3D {
 public:
  window3D();
  ~window3D();
  void addObject(const std::vector<cv::Point3f>& object_corners, const cv::Mat& tmat, const cv::Mat& rmat);

 private:
  void th_run();
  void setPatroon();
  sf::Thread thread;
  sf::Mutex mutex;
  volatile bool w_quit;
  volatile bool w_redraw;

  void makecube(GLBatch&);
  GLTriangleBatch omgeving;
  GLBatch patroon;
  GLShaderManager shadermanager;
  GLMatrixStack modelviewmatrix;
  GLMatrixStack projectionmatrix;
  GLFrame camera;
  GLFrustum viewfrustum;
  GLGeometryTransform transformpipeline;

  std::vector<cv::Point3f> o_corners;
  M3DMatrix33d o_translation;
  M3DMatrix33d o_rotation;
};
#endif /* WINDOW_3D_H_ */
