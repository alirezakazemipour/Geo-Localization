#ifndef SAVE_DATA_H
#define SAVE_DATA_H

#include <QObject>
#include <ros/ros.h>
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/NavSatFix.h>
#include <iostream>
#include <fstream>

class save_data : public QObject
{
    Q_OBJECT
public:
    explicit save_data(QObject *parent = 0);

    double Alt, Lon, Lat;

    void imuCallback(const sensor_msgs::Imu& msg);
    void gpsCallback(const sensor_msgs::NavSatFix& msg);
    std::ofstream log;

signals:

public slots:
};

#endif // SAVE_DATA_H
