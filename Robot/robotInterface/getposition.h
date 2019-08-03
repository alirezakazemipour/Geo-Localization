#ifndef GETPOSITION_H
#define GETPOSITION_H

#include <QObject>
#include <QUdpSocket>
#include <QUdpSocket>
#include "QDataStream"

class getPosition : public QObject
{
    Q_OBJECT
public:
    explicit getPosition(QObject *parent = 0);

    void ReadRecPacket(QByteArray data);
     QUdpSocket *rec_data_socket;
     int data_port;
     int cur_location;



signals:
     void current_loaction(int x);

public slots:
     void receive_data();
};

#endif // GETPOSITION_H
