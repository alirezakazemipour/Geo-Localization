#include "mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    //#ifdef Threading
    camera.moveToThread(&cam_thread);
    opt.moveToThread(&opt_thread);
    transmit.moveToThread(&transmit_thread);
    robot.moveToThread(&robot_thread);
    recieve.moveToThread(&recieve_thread);
    //#endif


    qRegisterMetaType< cv::Mat >("cv::Mat");
    qRegisterMetaType< string >("string");
    qRegisterMetaType< std::vector<cv::Point> >("std::vector<cv::Point>");

    connect(&timer,SIGNAL(timeout()),&camera,SLOT(downFrame_ready()));
    connect(&camera,SIGNAL(down_image_send(cv::Mat)),&transmit,SLOT(send(cv::Mat)));
    connect(&camera,SIGNAL(down_image_opt(cv::Mat)),&opt,SLOT(timerEvent(cv::Mat)));

    connect(&opt,SIGNAL(optSig(int,int)),&robot,SLOT(optFlow_CB(int,int)));

    connect(&recieve.rec_data_socket,SIGNAL(readyRead()),&recieve,SLOT(receive_data()));
    connect(&recieve,SIGNAL(current_loaction(int)),&robot,SLOT(location_CB(int)));
    //#ifdef Threading

    qDebug()<<"MW_T"<<QThread::currentThreadId();
    cam_thread.start();
    opt_thread.start();
    recieve_thread.start();
    robot_thread.start();
    //#endif
    timer.start(2);

}


MainWindow::~MainWindow()
{

}

