#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <capture.h>
#include <QTimer>
#include <sendimg.h>
#include <optflow.h>
#include <quad_board.h>
#include <QThread>
//#include <iostream>

Q_DECLARE_METATYPE(cv::Mat)
//Q_DECLARE_METATYPE(std::vector<cv::Point>)


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0 );
    ~MainWindow();
    capture camera;
    QTimer timer;
    sendImg transmit;

    OptFlow opt;
    Quad_Board robot;

    QThread cam_thread;
    QThread opt_thread;
    QThread transmit_thread;
    QThread robot_thread;
public slots:


};

#endif // MAINWINDOW_H

