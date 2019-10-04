#include "include/capture.h"

capture::capture(QObject *parent) : QObject(parent)
{

    path_img="/home/alireza/Desktop/bagFiles/robotImages/";



}

void capture::imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
    // double exec_time = (double)cv::getTickCount();

    try
    {
        cv::imshow("view", cv_bridge::toCvShare(msg, "bgr8")->image);
        frame=cv_bridge::toCvShare(msg, "bgr8")->image;
        cv::waitKey(3);

    }
    catch (cv_bridge::Exception& e)
    {
        ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
    }

    CurrTimeText = CurrTime.currentTime().toString("h:m:s.z");
    cvtColor(frame,frame,CV_RGB2GRAY);
    ImgPath=path_img+CurrTimeText;
    imwrite( QString(ImgPath + ".jpg").toLatin1().data(),
             frame);


    //    cap >> frame;
    //    emit(imageReady(frame));
    // exec_time = ((double)cv::getTickCount() - exec_time)*1000./cv::getTickFrequency();
    // qDebug()<<"exec_time = "<<exec_time;

}
