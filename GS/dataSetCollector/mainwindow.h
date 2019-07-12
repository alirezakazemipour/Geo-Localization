#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QUdpSocket>
#include <opencv2/opencv.hpp>
#include <QTime>
#include <QString>

using namespace cv;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QUdpSocket *rec_img_socket;


    int data_port;
    QByteArray datagram;
    Mat dec_mat;
    QTime CurrTime;
    QString ImgPath,CurrTimeText,path_img;
private:
    Ui::MainWindow *ui;

public slots:
    void receive_data();
};

#endif // MAINWINDOW_H
