#include <iostream>
#include <ros/ros.h>
#include <include/capture.h>
#include <include/save_data.h>
#include <image_transport/image_transport.h>
#include <QApplication>
#include <QThread>



int main( int argc, char* argv[] )
{
    QApplication a(argc,argv);

    ros::init( argc, argv, "saveData" );
    ros::NodeHandle n;
    image_transport::ImageTransport it(n);
    image_transport::Subscriber bgr_image_sub_;
    save_data logger;
    capture cap;

    ros::Subscriber imu = n.subscribe("/mavros/imu/data", 1,&save_data::imuCallback,&logger);
    ros::Subscriber gps = n.subscribe("/mavros/global_position/raw/fix", 1,&save_data::gpsCallback,&logger);

    bgr_image_sub_ = it.subscribe
            ("/usb_cam/image_raw",1,&capture::imageCallback,&cap);


    ROS_INFO("saveData node started");
    ros::spin();
    logger.log.close();
    return 0;
}
