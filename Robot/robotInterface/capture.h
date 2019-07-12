#ifndef CAPTURE_H
#define CAPTURE_H

#include <QObject>
#include <opencv2/opencv.hpp>
#include <QDebug>
#include <opencv2/opencv.hpp>
#include <QThread>


#define FRONT_CAM_NUM 1
#define DOWN_CAM_NUM 0

#define FRONT_FPS 30
#define DOWN_FPS 60

#define FRAME_WIDTH 320
#define FRAME_HEIGHT 240


using namespace cv;

class capture : public QObject  
{
    Q_OBJECT  
public:
    explicit capture(QObject *parent = 0);

    VideoCapture down_cam;

    Mat opt_frame;

    Mat down_frame;



signals:

   // void front_image(cv::Mat );
    void down_image_opt(cv::Mat );
    void down_image_send(cv::Mat );

public slots:
   // void frontFrame_ready();
    void downFrame_ready();

};

#endif // CAPTURE_H

