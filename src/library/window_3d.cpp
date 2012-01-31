#include "library.h"

window3D::window3D() : w_quit(false), w_redraw(true), thread(&window3D::th_run, this) {
  thread.Launch();
}

window3D::~window3D() {
  w_quit = true;
  thread.Wait();
}

void window3D::th_run() {
  sf::Window window(sf::VideoMode(640, 480),"3D view of pattern");
  static GLfloat vRed[] = {1.0f, 0.0f, 0.0f, 1.0f};
  static GLfloat vBlue[] = {0.0f, 0.0f, 1.0f, 1.0f};
  GLenum err = glewInit();
  if (GLEW_OK != err)
    {
      /* Problem: glewInit failed, something is seriously wrong. */
      fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  shadermanager.InitializeStockShaders();
  //makecube(this->omgeving);
  window.SetActive();
  glEnable(GL_DEPTH_TEST);
  transformpipeline.SetMatrixStacks(modelviewmatrix, projectionmatrix);
  camera.MoveForward(4.0f);
  gltMakeTorus(this->omgeving, .80f, 0.25f, 52, 26);
  while(!w_quit) {
    {
      sf::Lock lock(mutex);
      if(w_redraw) {
	setPatroon();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	modelviewmatrix.PushMatrix();
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(5.0f);
	shadermanager.UseStockShader(GLT_SHADER_FLAT, transformpipeline.GetModelViewProjectionMatrix(), vRed);
	omgeving.Draw();
	shadermanager.UseStockShader(GLT_SHADER_FLAT, transformpipeline.GetModelViewProjectionMatrix(), vBlue);
	patroon.Draw();
	modelviewmatrix.PopMatrix();
	window.Display();
	w_redraw = false;
      }
    }
  }
  window.Close();
}

void window3D::addObject(const std::vector<cv::Point3f>& object_corners, const cv::Mat& tmat, const cv::Mat& rmat) {
  sf::Lock lock(mutex);
  {
    o_corners = object_corners;
    int a = 0;
    cv::Mat mytmat, myrmat;
    tmat.copyTo(mytmat);
    rmat.copyTo(myrmat);
    for(int i = 0; i < mytmat.cols; i++)
      {
	const double* M = mytmat.ptr<double>(i);
	for(int j = 0; j < mytmat.rows; j++)
	  {
	    o_translation[a] = M[j];
	    a++;
	  }
      }
    a = 0;
    for(int i = 0; i < myrmat.cols; i++)
      {
	const double* M = myrmat.ptr<double>(i);
	for(int j = 0; j < myrmat.rows; j++)
	  {
	    o_rotation[a] = M[j];
	    a++;
	  }
      }
    w_redraw = true;
  }
}

void window3D::setPatroon() {
    patroon.Begin(GL_TRIANGLES, o_corners.size(), 1);
    for(int i = 0; i <o_corners.size(); i++) {
      patroon.Vertex3f(o_corners[i].x, o_corners[i].y, o_corners[i].z);
      //std::cout << o_corners[i].x << o_corners[i].y <<  o_corners[i].z << std::endl;
    }
    patroon.End();

}
void window3D:: makecube(GLBatch& cubeBatch)
{
  cubeBatch.Begin(GL_TRIANGLES, 36, 1);

  /////////////////////////////////////////////
  // Top of cube
  cubeBatch.Normal3f(0.0f, 1.0f, 0.0f);
  cubeBatch.MultiTexCoord2f(0, 1.0f, 1.0f);
  cubeBatch.Vertex3f(1.0f, 1.0f, 1.0f);

  cubeBatch.Normal3f(0.0f, 1.0f, 0.0f);
  cubeBatch.MultiTexCoord2f(0, 1.0f, 0.0f);
  cubeBatch.Vertex3f(1.0f, 1.0f, -1.0f);

  cubeBatch.Normal3f(0.0f, 1.0f, 0.0f);
  cubeBatch.MultiTexCoord2f(0, 0.0f, 0.0f);
  cubeBatch.Vertex3f(-1.0f, 1.0f, -1.0f);

  cubeBatch.Normal3f(0.0f, 1.0f, 0.0f);
  cubeBatch.MultiTexCoord2f(0, 1.0f, 1.0f);
  cubeBatch.Vertex3f(1.0f, 1.0f, 1.0f);

  cubeBatch.Normal3f(0.0f, 1.0f, 0.0f);
  cubeBatch.MultiTexCoord2f(0, 0.0f, 0.0f);
  cubeBatch.Vertex3f(-1.0f, 1.0f, -1.0f);

  cubeBatch.Normal3f(0.0f, 1.0f, 0.0f);
  cubeBatch.MultiTexCoord2f(0, 0.0f, 1.0f);
  cubeBatch.Vertex3f(-1.0f, 1.0f, 1.0f);


  ////////////////////////////////////////////
  // Bottom of cube
  cubeBatch.Normal3f(0.0f, -1.0f, 0.0f);
  cubeBatch.MultiTexCoord2f(0, 0.0f, 0.0f);
  cubeBatch.Vertex3f(-1.0f, -1.0f, -1.0f);

  cubeBatch.Normal3f(0.0f, -1.0f, 0.0f);
  cubeBatch.MultiTexCoord2f(0, 1.0f, 0.0f);
  cubeBatch.Vertex3f(1.0f, -1.0f, -1.0f);

  cubeBatch.Normal3f(0.0f, -1.0f, 0.0f);
  cubeBatch.MultiTexCoord2f(0, 1.0f, 1.0f);
  cubeBatch.Vertex3f(1.0f, -1.0f, 1.0f);

  cubeBatch.Normal3f(0.0f, -1.0f, 0.0f);
  cubeBatch.MultiTexCoord2f(0, 0.0f, 1.0f);
  cubeBatch.Vertex3f(-1.0f, -1.0f, 1.0f);

  cubeBatch.Normal3f(0.0f, -1.0f, 0.0f);
  cubeBatch.MultiTexCoord2f(0, 0.0f, 0.0f);
  cubeBatch.Vertex3f(-1.0f, -1.0f, -1.0f);

  cubeBatch.Normal3f(0.0f, -1.0f, 0.0f);
  cubeBatch.MultiTexCoord2f(0, 1.0f, 1.0f);
  cubeBatch.Vertex3f(1.0f, -1.0f, 1.0f);

  ///////////////////////////////////////////
  // Left side of cube
  cubeBatch.Normal3f(-1.0f, 0.0f, 0.0f);
  cubeBatch.MultiTexCoord2f(0, 1.0f, 1.0f);
  cubeBatch.Vertex3f(-1.0f, 1.0f, 1.0f);

  cubeBatch.Normal3f(-1.0f, 0.0f, 0.0f);
  cubeBatch.MultiTexCoord2f(0, 1.0f, 0.0f);
  cubeBatch.Vertex3f(-1.0f, 1.0f, -1.0f);

  cubeBatch.Normal3f(-1.0f, 0.0f, 0.0f);
  cubeBatch.MultiTexCoord2f(0, 0.0f, 0.0f);
  cubeBatch.Vertex3f(-1.0f, -1.0f, -1.0f);

  cubeBatch.Normal3f(-1.0f, 0.0f, 0.0f);
  cubeBatch.MultiTexCoord2f(0, 1.0f, 1.0f);
  cubeBatch.Vertex3f(-1.0f, 1.0f, 1.0f);

  cubeBatch.Normal3f(-1.0f, 0.0f, 0.0f);
  cubeBatch.MultiTexCoord2f(0, 0.0f, 0.0f);
  cubeBatch.Vertex3f(-1.0f, -1.0f, -1.0f);

  cubeBatch.Normal3f(-1.0f, 0.0f, 0.0f);
  cubeBatch.MultiTexCoord2f(0, 0.0f, 1.0f);
  cubeBatch.Vertex3f(-1.0f, -1.0f, 1.0f);

  // Right side of cube
  cubeBatch.Normal3f(1.0f, 0.0f, 0.0f);
  cubeBatch.MultiTexCoord2f(0, 0.0f, 0.0f);
  cubeBatch.Vertex3f(1.0f, -1.0f, -1.0f);

  cubeBatch.Normal3f(1.0f, 0.0f, 0.0f);
  cubeBatch.MultiTexCoord2f(0, 1.0f, 0.0f);
  cubeBatch.Vertex3f(1.0f, 1.0f, -1.0f);

  cubeBatch.Normal3f(1.0f, 0.0f, 0.0f);
  cubeBatch.MultiTexCoord2f(0, 1.0f, 1.0f);
  cubeBatch.Vertex3f(1.0f, 1.0f, 1.0f);

  cubeBatch.Normal3f(1.0f, 0.0f, 0.0f);
  cubeBatch.MultiTexCoord2f(0, 1.0f, 1.0f);
  cubeBatch.Vertex3f(1.0f, 1.0f, 1.0f);

  cubeBatch.Normal3f(1.0f, 0.0f, 0.0f);
  cubeBatch.MultiTexCoord2f(0, 0.0f, 1.0f);
  cubeBatch.Vertex3f(1.0f, -1.0f, 1.0f);

  cubeBatch.Normal3f(1.0f, 0.0f, 0.0f);
  cubeBatch.MultiTexCoord2f(0, 0.0f, 0.0f);
  cubeBatch.Vertex3f(1.0f, -1.0f, -1.0f);

  // Front and Back
  // Front
  cubeBatch.Normal3f(0.0f, 0.0f, 1.0f);
  cubeBatch.MultiTexCoord2f(0, 1.0f, 0.0f);
  cubeBatch.Vertex3f(1.0f, -1.0f, 1.0f);

  cubeBatch.Normal3f(0.0f, 0.0f, 1.0f);
  cubeBatch.MultiTexCoord2f(0, 1.0f, 1.0f);
  cubeBatch.Vertex3f(1.0f, 1.0f, 1.0f);

  cubeBatch.Normal3f(0.0f, 0.0f, 1.0f);
  cubeBatch.MultiTexCoord2f(0, 0.0f, 1.0f);
  cubeBatch.Vertex3f(-1.0f, 1.0f, 1.0f);

  cubeBatch.Normal3f(0.0f, 0.0f, 1.0f);
  cubeBatch.MultiTexCoord2f(0, 0.0f, 1.0f);
  cubeBatch.Vertex3f(-1.0f, 1.0f, 1.0f);

  cubeBatch.Normal3f(0.0f, 0.0f, 1.0f);
  cubeBatch.MultiTexCoord2f(0, 0.0f, 0.0f);
  cubeBatch.Vertex3f(-1.0f, -1.0f, 1.0f);

  cubeBatch.Normal3f(0.0f, 0.0f, 1.0f);
  cubeBatch.MultiTexCoord2f(0, 1.0f, 0.0f);
  cubeBatch.Vertex3f(1.0f, -1.0f, 1.0f);

  // Back
  cubeBatch.Normal3f(0.0f, 0.0f, -1.0f);
  cubeBatch.MultiTexCoord2f(0, 1.0f, 0.0f);
  cubeBatch.Vertex3f(1.0f, -1.0f, -1.0f);

  cubeBatch.Normal3f(0.0f, 0.0f, -1.0f);
  cubeBatch.MultiTexCoord2f(0, 0.0f, 0.0f);
  cubeBatch.Vertex3f(-1.0f, -1.0f, -1.0f);

  cubeBatch.Normal3f(0.0f, 0.0f, -1.0f);
  cubeBatch.MultiTexCoord2f(0, 0.0f, 1.0f);
  cubeBatch.Vertex3f(-1.0f, 1.0f, -1.0f);

  cubeBatch.Normal3f(0.0f, 0.0f, -1.0f);
  cubeBatch.MultiTexCoord2f(0, 0.0f, 1.0f);
  cubeBatch.Vertex3f(-1.0f, 1.0f, -1.0f);

  cubeBatch.Normal3f(0.0f, 0.0f, -1.0f);
  cubeBatch.MultiTexCoord2f(0, 1.0f, 1.0f);
  cubeBatch.Vertex3f(1.0f, 1.0f, -1.0f);

  cubeBatch.Normal3f(0.0f, 0.0f, -1.0f);
  cubeBatch.MultiTexCoord2f(0, 1.0f, 0.0f);
  cubeBatch.Vertex3f(1.0f, -1.0f, -1.0f);

  cubeBatch.End();
}
