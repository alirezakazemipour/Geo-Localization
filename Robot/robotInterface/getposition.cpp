#include "getposition.h"

getPosition::getPosition(QObject *parent) : QObject(parent)
{
    data_port=5678;
    rec_data_socket = new QUdpSocket(this);
    rec_data_socket->bind(data_port);

}

void getPosition::ReadRecPacket(QByteArray data)
{
    QByteArray datagram,StartPacket;
    datagram=data;
    QDataStream RecDataStream(&datagram , QIODevice::ReadOnly);

    RecDataStream >> StartPacket;

    if( QString::compare(StartPacket,"St") == 0 )
        RecDataStream >> cur_location;

    datagram.clear();

}

void getPosition::receive_data()
{
    //qDebug() << "rec";
    QByteArray datagram;
    datagram.resize(rec_data_socket->pendingDatagramSize());
    rec_data_socket->readDatagram(datagram.data(), datagram.size());
    rec_data_socket->flush();
    ReadRecPacket(datagram);
    datagram.clear();

    qDebug() << "cur_location: " << cur_location;
    emit current_loaction(cur_location);
}

