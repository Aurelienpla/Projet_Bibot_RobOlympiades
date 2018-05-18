#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace std;
using namespace cv;

//HSV de la couleur verte
Scalar lowerGreen = Scalar(33, 97, 0);
Scalar higherGreen = Scalar(94, 255, 255);

//Parameters camera
const int FRAME_WIDTH = 640;
const int FRAME_HEIGHT = 360;

//Matrice image
Mat source;
Mat HSV;
Mat HSV_threshold;
Mat gray;
Mat imgBlur;
Mat canny;
Mat thresh;
Mat camerademerde;

VideoCapture capture;

//Vector findContours
vector<vector<Point> > contours;
vector<Vec4i> hierarchy;

int canny_thresh_1 = 100;
int canny_thresh_2 = 200;
int area = 0;
int max_area = 0;

//Parameters for HSV
int iLowH = lowerGreen[0];
int iHighH = higherGreen[0];
int iLowS = lowerGreen[1];
int iHighS = higherGreen[1];
int iLowV = lowerGreen[2];
int iHighV = higherGreen[2];

void onHSVTrackBar(int, void*){

    Mat textHSV = Mat::zeros( Size(600, 200), CV_8UC3 );
    string textH = "Tein-L: "; textH += to_string(iLowH); textH+= "   Tein-H: "; textH += to_string(iHighH);
    string textS = "Satu-L: "; textS += to_string(iLowS); textS+= "   Satu-H: "; textS += to_string(iHighS);
    string textV = "Lumi-L: "; textV += to_string(iLowV); textV+= "   Lumi-H: "; textV += to_string(iHighV);
    int font = FONT_HERSHEY_SIMPLEX;
    putText(textHSV, textH, Point(0, 50), font, 1, Scalar(0, 255, 0), 1, 8);
    putText(textHSV, textS, Point(0, 100), font, 1, Scalar(0, 255, 0), 1, 8);
    putText(textHSV, textV, Point(0, 150), font, 1, Scalar(0, 255, 0), 1, 8);
    imshow("HSV", textHSV);
}

int main()
{
    namedWindow( "Source", CV_WINDOW_AUTOSIZE );
    namedWindow( "Canny", CV_WINDOW_AUTOSIZE);
    //namedWindow( "Drawing", CV_WINDOW_AUTOSIZE);
    namedWindow( "HSV", CV_WINDOW_NORMAL);
    resizeWindow("HSV", Size(600, 100));

    capture.open(1);

    //set height and width of capture frame
    capture.set(CV_CAP_PROP_FRAME_WIDTH,FRAME_WIDTH);
    capture.set(CV_CAP_PROP_FRAME_HEIGHT,FRAME_HEIGHT);

    if(!capture.isOpened())  // check if we succeeded
        return -1;

    //Create trackbars in "HSV" window
    createTrackbar("Tein-L", "HSV", &iLowH, 179, onHSVTrackBar); //Hue (0 - 179)
    createTrackbar("Tein-H", "HSV", &iHighH, 179, onHSVTrackBar);

    createTrackbar("Satu-L", "HSV", &iLowS, 255, onHSVTrackBar); //Saturation (0 - 255)
    createTrackbar("Satu-H", "HSV", &iHighS, 255, onHSVTrackBar);

    createTrackbar("Lumi-L", "HSV", &iLowV, 255, onHSVTrackBar); //Value (0 - 255)
    createTrackbar("Lumi-H", "HSV", &iHighV, 255, onHSVTrackBar);

    onHSVTrackBar(0,0);

    while(1){
        capture.read(camerademerde);
        //camerademerde = imread("/Users/Byakotaku/Desktop/Cobinov/Adventices/Adventice1.jpg", IMREAD_COLOR);
        cvtColor(camerademerde, HSV, COLOR_BGR2HSV);

        //********************************************************************************************************

        inRange(HSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), HSV_threshold); //Threshold the image

        //morphological opening (remove small objects from the foreground)
        erode( HSV_threshold, HSV_threshold, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
        dilate( HSV_threshold, HSV_threshold, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

         //morphological closing (fill small holes in the foreground)
        dilate( HSV_threshold, HSV_threshold, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
        erode( HSV_threshold, HSV_threshold, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

        Canny(HSV_threshold, canny, 100, 200, 3);

        imshow("Canny", canny);

        findContours(canny, contours, hierarchy, RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0,0));

        // Approximate contours to polygons + get bounding rects and circles
        vector<vector<Point> > contours_poly( contours.size() );
        vector<Rect> boundRect( contours.size() );

        Mat drawing = Mat::zeros( canny.size(), CV_8UC3 );
        for( int i = 0; i < contours.size(); i++ )
        {
            approxPolyDP( Mat(contours[i]), contours_poly[i], 5, true );
            boundRect[i] = boundingRect( Mat(contours_poly[i]) );

            drawContours( drawing, contours, i, Scalar(255, 0, 0), 2, 8, hierarchy, INT_MAX, Point() );

            if(boundRect[i].width > 80 || boundRect[i].height > 80){
                Point rectCenter(boundRect[i].x+(boundRect[i].width/2), boundRect[i].y+(boundRect[i].height/2));
                Scalar color = Scalar(0, 255, 0);

                rectangle( camerademerde, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0 );
                circle(camerademerde, rectCenter, 1, color, 3);
                putText(camerademerde, "Center", Point(rectCenter.x+30, rectCenter.y-20),
                        FONT_HERSHEY_SIMPLEX, 0.6, color, 2, 8);
            }
        }
        imshow("Source", camerademerde);

        //********************************************************************************************************

        if(waitKey(30) >= 0)break;
    }

    // Destroy the windows we have created
    cvDestroyWindow("HSV");
    cvDestroyWindow("Source");
    cvDestroyWindow("Canny");

    // Destroy the capture
    capture.release();

    return 0;
}


