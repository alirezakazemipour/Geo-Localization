#ifndef SENDIMG_H
#define SENDIMG_H

#include <QObject>
#include <QDebug>
#include <QUdpSocket>
#include <opencv2/opencv.hpp>

using namespace cv;

class sendImg : public QObject
{
    Q_OBJECT
public:
    explicit sendImg(QObject *parent = 0);

    QByteArray robot_data;
    QHostAddress *GS_IP;
    QUdpSocket *send_img_socket;
    int GS_img_port;
    std::vector<uchar> enc_buff;
    std::vector<int> compression_params;
    QByteArray img_data;

signals:

public slots:
    void send(Mat b);
};

#endif // SENDIMG_H
