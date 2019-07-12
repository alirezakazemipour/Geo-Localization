#include "sendimg.h"

sendImg::sendImg(QObject *parent) : QObject(parent)
{
    GS_IP = new QHostAddress("127.0.0.1");
    send_img_socket = new QUdpSocket(this);
    GS_img_port=1234;

    compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
    compression_params.push_back(60);

}

void sendImg::send(Mat b)
{
    //if (img_data.size()>65535) //more than 64kB (65536)

    imencode(".jpg",b,enc_buff,compression_params);
    unsigned int size=enc_buff.size();
    img_data.resize(size);
    for(unsigned int i=0; i<size; i++)
        img_data[i]=(unsigned char)enc_buff[i];
    send_img_socket->writeDatagram(img_data, *GS_IP, GS_img_port);
    send_img_socket->flush();
    img_data.clear();
    enc_buff.clear();
    qDebug() << "slot";
//    imshow("frame",b);
}

