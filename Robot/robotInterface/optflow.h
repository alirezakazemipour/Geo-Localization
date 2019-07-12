#ifndef OPTFLOW_H
#define OPTFLOW_H

#include <opencv2/opencv.hpp>
#include "QThread"
#include "QDebug"
#include "QTime"
#include <QObject>

//#define _GRAPH
#define _Serial


#define MAX_COUNT               20
#define THRESH_REFRESH          8

#define winSize                 Size(17,17)
#define subPixWinSize           Size(5,5)

using namespace cv;
using namespace std;


class OptFlow: public QObject
{
    Q_OBJECT

public:
    explicit OptFlow(QObject *parent = 0);
    ~OptFlow();


    Mat colorframe, grayframe;
    QTime d;

    Mat prevGray, image;
    vector<Point2f> points[2];
    TermCriteria termcrit;
    Point2f point;

    bool needToInit;
    bool done;

    size_t Features_counter;//count Features state true

    double delta_x, delta_y;

    int dx,dy;

    void OptFlow_LK();

signals:
    void optSig(int, int);
//private:
    //Quad_Board *transmiter;

public slots:
    void timerEvent(cv::Mat raw_image);
};

#endif // OPTFLOW_H
