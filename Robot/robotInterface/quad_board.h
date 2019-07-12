#ifndef QUAD_BOARD_H
#define QUAD_BOARD_H

#include <QObject>
//#include <QtExtSerialPort/qextserialport.h>
#include <qextserialport.h>
#include "qdebug.h"


#define _DEV_SERIAL            "/dev/ttySAC0"
//"/dev/ttyUSB0"
//#define MPC_BUFF_AMOUNT  11


class Quad_Board : public QObject
{
    Q_OBJECT
public:
    explicit Quad_Board(QObject *parent = 0);
    ~Quad_Board();

    //void decode(uchar data);

    union _ch2int
        {
            int16_t real;
            char byte[2];
        };


    typedef union _ch2int  ch2int;



    void Mpc_decode(u_int8_t _data);
    void Empty_Data();
    void Fill_Data(uchar num , ... );
    void Send_Data();

public:

    bool ready;
    char decode_stage;
    char sum;
    char received_packet_length;
    int integer_received_counter;
    int data_num;
    int data_recieved[32];
    int16_t data[32];
    int j;
    int Len;
    int pack_started;
    QByteArray data_send;
    uchar Num;
    uchar check_Sum;
    QextSerialPort *serial_port;
    ch2int conv;
  //  void window_CB(const serial_handler::WinMsg &msg);
    int load[8]={0,0,0,0,0,0,0,0};

public slots:
    void readData();
    void lineSerial_CB(double dist, double angle,int hassan);
    void gateSerial_CB(int movement);
    void landingPadSerial_CB(int land);
    void optFlow_CB(int delta_x , int delta_y);




};




#endif // QUAD_BOARD_H
