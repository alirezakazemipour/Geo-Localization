#include "save_data.h"

save_data::save_data(QObject *parent) : QObject(parent)
{

    log.open("/home/alireza/Desktop/bagFiles/log.txt");

}

void save_data::imuCallback(const sensor_msgs::Imu& msg)
{
    std::cout<<"Linear acc = "<<msg.linear_acceleration.x<<std::endl;

}

void save_data::gpsCallback(const sensor_msgs::NavSatFix &msg)
{
    std::cout << std::setprecision(9);
    std::cout<<"Latitude = "<<msg.latitude<<std::endl;
    std::cout << std::setprecision(9);
    std::cout<<"Longtitude = "<<msg.latitude<<std::endl;
    Lon = msg.longitude;
    Lat = msg.latitude;
    log<< std::setprecision(9);
    log<<Lat<< std::setprecision(9)<<","<<Lon<< std::setprecision(9)<<std::endl;
}

