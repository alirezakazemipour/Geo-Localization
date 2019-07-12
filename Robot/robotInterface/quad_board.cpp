#include "quad_board.h"



Quad_Board::Quad_Board(QObject *parent) : QObject(parent)
{
        QString portName = QLatin1String(_DEV_SERIAL);
        serial_port =  new QextSerialPort(QString(portName), QextSerialPort::EventDriven);
        serial_port->close();
        serial_port->setPortName(_DEV_SERIAL);

        serial_port->open(QIODevice::ReadWrite);

        serial_port->setBaudRate(BAUD115200);
        serial_port->setParity(PAR_NONE);   
        serial_port->setFlowControl(FLOW_OFF);
        serial_port->setDataBits(DATA_8);
        serial_port->setStopBits(STOP_1);

        serial_port->setDtr(0);
        serial_port->setRts(0);

        serial_port->flush();

  

    ready = false;
    decode_stage = 0;
    sum = 0;
    j=0;
    integer_received_counter = 0;
    Num = 0;
       if( serial_port->isOpen())
        {
            qDebug("Serial Port Opened  .");
        }
        else
        {
            qDebug("Serial Port NOT Opened!!!!!!!");
            exit(0);

        }
     connect(serial_port, SIGNAL(readyRead()), this, SLOT(readData()));
}

Quad_Board::~Quad_Board()
{

}

void Quad_Board::Mpc_decode(u_int8_t _data)
{
    switch(pack_started)
    {

    case 0:
        if(_data == 0xff)
            pack_started = 1;
        else
            pack_started = 0;
        break;

    case 1:
        if(_data == 0xff)
            pack_started = 2;
        else
            pack_started = 0;
        break;

    case 2:
        Len =_data - 3;
        pack_started = 3;
        break;

    case 3:
        if(_data == 0)
            pack_started = 4;
        else
            pack_started = 0;
        break;
    case 4:

        if( Len == 0)
        {

            sum =  sum + (u_int8_t)_data;
            if( sum == 0)
            {
                sum=0;
                pack_started =0;
                ready =1;
                data_num =  j;
                j=0;
            }
            else
            {
                j=0;
                sum=0;
                pack_started =0;
            }

        }
        else
        {
            sum =  sum + (u_int8_t)_data;
            conv.byte[0] = _data;
            pack_started =5;
        }
        break;
    case 5:
        sum =  sum + (u_int8_t)_data;
        conv.byte[1] = _data;
        pack_started =4;
        data[j] =  conv.real;
        Len =  Len - 2;
        j++;
        break;

    }

}


void Quad_Board::Empty_Data()
{
    Num = 0;
    check_Sum = 0;
    data_send.clear();
    data_send.append(QByteArray::fromHex("FF"));
    data_send.append(QByteArray::fromHex("FF"));

}

void Quad_Board::Fill_Data(uchar num,...)
{
    va_list arguments;
    va_start( arguments, num );

    Empty_Data();
    data_send.append(((num * 2) + 3));
    data_send.append(Num);
    for(int i = 0; i < num; i++)
    {
        conv.real=(uint)va_arg( arguments, int );
        //qDebug()<<conv.real;
        check_Sum = check_Sum + (uchar)conv.byte[0] + (uchar)conv.byte[1];
        data_send.append(conv.byte[0]);
        data_send.append(conv.byte[1]);
    }
    Send_Data();

    va_end ( arguments );

}

void Quad_Board::Send_Data()
{
    data_send.append((~(check_Sum) + 1));
    serial_port->write(data_send);
    //qDebug()<<data_send.toHex();
   serial_port->flush();

}

void Quad_Board::lineSerial_CB(double dist, double angle,int hassan)
{
//
   // ROS_WARN("line running %d",dist.dx);
    load[2]=18;
    load[3]=int(dist);
    load[4]=int(angle);
            qDebug()<<"h"<<hassan;
    load[7] = hassan;
  //  load[5]=dist.direction;

}

void Quad_Board::gateSerial_CB(int movement)
{
    load[5]=movement;
    //qDebug()<<"Gate Data"<<load[5];
    //	0 down
    
    // 1 up

}

void Quad_Board::landingPadSerial_CB(int land)
{
    load[6]=land;
    qDebug()<<"H Data"<<load[6];
    //if 1 = landing pad existance
}

/*void Quad_Board::window_CB(const serial_handler::WinMsg &msg)
{

    qDebug()<<"WINDOW!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! "<<msg.setpoint;
    load[2]=msg.setpoint;
    load[3]=msg.flag;
    load[4]=msg.scale;
    load[5]=msg.upperbound;
}*/

void Quad_Board::optFlow_CB(int delta_x, int delta_y)
{
   // qDebug()<<"optical!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! = "<<msg.delta_x;
    load[0]=delta_x;
    load[1]=delta_y;
// qDebug()<<load[2]<<" "<<load[3]<<" "<<load[4]<<" "<<load[5]<<endl;
Fill_Data(8,load[0],load[1],load[2],load[3],load[4],load[5],load[6],load[7]);

}
void Quad_Board::readData()
{
     QByteArray _data = serial_port->readAll();
    unsigned char a;

    //qDebug() << "read*";
    //printf("read\n");

        for (int i=0;i<_data.size();i++)
        {
            a=_data.at(i) ;
            Mpc_decode(a);
        }


}


