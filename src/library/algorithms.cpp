/*
 * algorithms.cpp
 *
 *  Created on: Nov 25, 2011
 *      Author: stephan
 */

#include "library.h"

namespace alg
{
/************************************
 * BEGIN NAMESPACE ALG
 * **********************************/
image_resource change_color_space(const image_resource& input, const int code)
{
    using namespace cv;
    image_resource output;
    cvtColor(input.get_resource(), output.get_resource(), code);
    return output;
}
image_resource threshold(const image_resource& input, const double thresh, const double max,
                          const int type)
{
    using namespace cv;
    image_resource output;
    threshold(input.get_resource(), output.get_resource(), thresh, max, type);
    return output;
}
}
/* **********************************
 * EINDE NAMESPACE SEGMENTATION
 * **********************************/

/* **********************************
 * BEGIN NAMESPACE DETECTION
 * **********************************/
namespace detection
{

/**
 * angle() is een hulpfunctie voor findSquares()
 */
double angle(cv::Point pt1, cv::Point pt2, cv::Point pt0)
{
    double dx1 = pt1.x - pt0.x;
    double dy1 = pt1.y - pt0.y;
    double dx2 = pt2.x - pt0.x;
    double dy2 = pt2.y - pt0.y;
    return (dx1 * dx2 + dy1 * dy2)
           / sqrt((dx1 * dx1 + dy1 * dy1) * (dx2 * dx2 + dy2 * dy2) + 1e-10);
}

std::vector<std::vector<cv::Point> > findSquares(const image_resource& input)
{
    using namespace std;
    using namespace cv;

    std::vector<std::vector<cv::Point> > squares;
    //waardes voor threshold levels
    int thresh = 50, N = 11;
    squares.clear();

    Mat pyr, timg, gray0(input.get_resource().size(), CV_8U), gray;

    // down-scale and upscale the image to filter out the noise
    pyrDown(input.get_resource(), pyr, Size(input.get_resource().cols / 2, input.get_resource().rows / 2));
    pyrUp(pyr, timg, input.get_resource().size());
    vector<vector<Point> > contours;

    // find squares in every color plane of the image
    for (int c = 0; c < 3; c++)
    {
        int ch[] = { c, 0 };
        mixChannels(&timg, 1, &gray0, 1, ch, 1);

        // try several threshold levels
        for (int l = 0; l < N; l++)
        {
            // hack: use Canny instead of zero threshold level.
            // Canny helps to catch squares with gradient shading
            if (l == 0)
            {
                // apply Canny. Take the upper threshold from slider
                // and set the lower to 0 (which forces edges merging)
                Canny(gray0, gray, 0, thresh, 5);
                // dilate canny output to remove potential
                // holes between edge segments
                dilate(gray, gray, Mat(), Point(-1, -1));
            }
            else
            {
                // apply threshold if l!=0:
                //     tgray(x,y) = gray(x,y) < (l+1)*255/N ? 255 : 0
                gray = gray0 >= (l + 1) * 255 / N;
            }

            // find contours and store them all as a list
            findContours(gray, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);

            vector<Point> approx;

            // test each contour
            for (size_t i = 0; i < contours.size(); i++)
            {
                // approximate contour with accuracy proportional
                // to the contour perimeter
                approxPolyDP(Mat(contours[i]), approx,
                             arcLength(Mat(contours[i]), true) * 0.02, true);

                // square contours should have 4 vertices after approximation
                // relatively large area (to filter out noisy contours)
                // and be convex.
                // Note: absolute value of an area is used because
                // area may be positive or negative - in accordance with the
                // contour orientation
                if (approx.size() == 4 && fabs(contourArea(Mat(approx))) > 1000
                        && isContourConvex(Mat(approx)))
                {
                    double maxCosine = 0;

                    for (int j = 2; j < 5; j++)
                    {
                        // find the maximum cosine of the angle between joint edges
                        double cosine = fabs(
                                            angle(approx[j % 4], approx[j - 2],
                                                  approx[j - 1]));
                        maxCosine = MAX(maxCosine, cosine);
                    }

                    // if cosines of all angles are small
                    // (all angles are ~90 degree) then write quandrange
                    // vertices to resultant sequence
                    if (maxCosine < 0.3)
                        squares.push_back(approx);
                }
            }
        }
    }
    return squares;
}

image_resource drawSquares(const image_resource& input,
                           const std::vector<std::vector<cv::Point> >& squares)
{
    using namespace cv;
    image_resource output(input.get_resource());
    for (size_t i = 0; i < squares.size(); i++)
    {
        const Point* p = &squares[i][0];
        int n = (int) squares[i].size();
        polylines(output.get_resource(), &p, &n, 1, true, Scalar(0, 255, 0), 3, CV_AA);
    }
    return output;
}

calibrationParameters calibrateCamera(const int n_boards, const int board_w, const int board_h, const video_resource& cam)
{
    using namespace cv;
    //boost::scoped_ptr<Webcam> cam;

    //int n_boards Number of pictures taken
    //int board_w Board width in squares
    //int board_h Board height in squares

    float boardScaleFactor = 25; // Chessboard square edge length in units you want to use

    int numCorners = board_h * board_w;
    Size board_size = Size(board_w, board_h);

    vector<Point2f> corners;
    vector<Point3f> object_corners;

    vector<vector<Point2f> > image_points;
    vector<vector<Point3f> > object_points;

    int successes = 0;

    for (int i = 0; i < numCorners; ++i)
    {
        object_corners.push_back(Point3f(boardScaleFactor*(i / board_h), boardScaleFactor*(i % board_h), 0.0f));
    }

    namedWindow("Calibration", 1);
    Mat img;
    Mat gray_img;
    int c;
    while (successes < n_boards)
    {
        while (waitKey(30) < 0)
        {
            img = cam.get_resource();

            if (!img.empty())
            {
                imshow("Calibration", img);
            }
            displayOverlay("Calibration", "Press any key to take a picture", 1);
        }
        bool patternFound = findChessboardCorners(img, board_size, corners, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);

        if (patternFound)
        {
            cvtColor(img, gray_img, CV_BGR2GRAY); // Convert to gray image for cornerSubPix

            cornerSubPix(gray_img, corners, Size(11,11), Size(-1,-1), TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 30, 0.1));
            drawChessboardCorners(img, board_size, corners, patternFound);

            imshow("Calibration", img);
            displayOverlay("Calibration", "Press S to save calibration image or any other key to discard it", 1);
            c = waitKey(0);

            if (c == 's' || c == 'S')
            {
                image_points.push_back(corners);
                object_points.push_back(object_corners);
                imshow("Calibration", gray_img);
                displayOverlay("Calibration", "Calibration image saved. Press any key to continue", 1);
                successes++;
                waitKey(0);
            }
            else
            {
                imshow("Calibration", img);
                displayOverlay("Calibration", "Calibration image discarded. Press any key to continue", 1);
                waitKey(0);
            }
        }
        else
        {
            imshow("Calibration", img);
            displayOverlay("Calibration", "Could not detect calibration pattern in image. Press any key to continue", 1);
            waitKey(0);
        }
    } // End of collection loop

    Mat intrinsic_matrix(3,3,CV_32FC1);
    Mat distortion_coeffs;
    vector<Mat> rvecs;
    vector<Mat> tvecs;

    intrinsic_matrix.ptr<float>(0)[0] = 1;
    intrinsic_matrix.ptr<float>(1)[1] = 1;

    // Calibrate camera
    // NB: Converts matrices to 64bit versions
    calibrateCamera(object_points, image_points, img.size(), intrinsic_matrix, distortion_coeffs, rvecs, tvecs);

    std::cout << "Intrinsic matrix after calibration:" << std::endl;
    std::cout << intrinsic_matrix.at<double>(0,0) << " " << intrinsic_matrix.at<double>(0,1) << " " << intrinsic_matrix.at<double>(0,2) << std::endl;
    std::cout << intrinsic_matrix.at<double>(1,0) << " " <<  intrinsic_matrix.at<double>(1,1)<< " " << intrinsic_matrix.at<double>(1,2) << std::endl;
    std::cout << intrinsic_matrix.at<double>(2,0) << " " << intrinsic_matrix.at<double>(2,1) << " " << intrinsic_matrix.at<double>(2,2) << std::endl;

    std::cout << "Distortion coefficients:" << std::endl;
    std::cout << distortion_coeffs.at<double>(0,0) << " " << distortion_coeffs.at<double>(0,1) << " " << distortion_coeffs.at<double>(0,2) << " " << distortion_coeffs.at<double>(0,3) << std::endl;

    return calibrationParameters(intrinsic_matrix, distortion_coeffs, board_w, board_h);
}

void findChessBoard(const calibrationParameters& cp, const image_resource& img)
{
    using namespace cv;

    float boardScaleFactor = 25;
    std::string window;
    int numCorners = cp.board_h * cp.board_w;
    Size board_size = Size(cp.board_w, cp.board_h);
    std::string loc;
    std::string rot;
    Mat rvec, tvec;

    vector<Point3f> object_corners;
    vector<Point2f> corners;

    for (int i = 0; i < numCorners; ++i)
    {
        object_corners.push_back(Point3f(boardScaleFactor*(i / cp.board_h), boardScaleFactor*(i % cp.board_h), 0.0f));
    }

    bool patternFound = findChessboardCorners(img.get_resource(), board_size, corners, CALIB_CB_FAST_CHECK);
    drawChessboardCorners(img.get_resource(), board_size, corners, patternFound);

    if (patternFound && (int)corners.size() == numCorners)
    {
        solvePnP(Mat(object_corners), Mat(corners), cp.intrinsic_parameters,cp.distortion_coeffs,rvec,tvec,false);
        //loc = "x: " + boost::lexical_cast<std::string>((int)tvec.at<double>(0,0)) + ' '
        //  + "y: " + boost::lexical_cast<std::string>((int)tvec.at<double>(0,1)) + ' '
        //  + "z: " + boost::lexical_cast<std::string>((int)tvec.at<double>(0,2));
        //putText(img, loc,
        //    Point(0,60), FONT_HERSHEY_PLAIN, 1, CV_RGB(255,0,255));
        Mat rmat;
        Rodrigues(rvec,rmat);
        double roll, pitch, yaw;
        roll = atan2(rmat.at<double>(1,0),rmat.at<double>(0,0));
        pitch = -asin(rmat.at<double>(2,0));
        yaw = atan2(rmat.at<double>(2,1),rmat.at<double>(2,2));
        //rot = "roll (z): " + boost::lexical_cast<std::string>((int)(roll*180/3.1415)) + ' '
        //  + "pitch (y): " + boost::lexical_cast<std::string>((int)(pitch*180/3.1415)) + ' '
        //  + "yaw (x): " + boost::lexical_cast<std::string>((int)(yaw*180/3.1415));
        //putText(img, rot,
        //    Point(0,75), FONT_HERSHEY_PLAIN, 1, CV_RGB(255,0,255));
    }
    //print het translatiematrix
    std::cout << "translatiematrix: " << std::endl;
    for(int i = 0; i < tvec.rows; i++)
    {
        const double* M = tvec.ptr<double>(i);
        for(int j = 0; j < tvec.cols; j++)
        {
            std::cout << M[j] << std::endl;
        }
    }
    //print het rotatiematrix
    std::cout << "rotatiematrix: " << std::endl;
    for(int i = 0; i < rvec.rows; i++)
    {
        const double* M = rvec.ptr<double>(i);
        for(int j = 0; j < rvec.cols; j++)
        {
            std::cout << M[j] << std::endl;
        }
    }
    imshow(window, img.get_resource());
}
