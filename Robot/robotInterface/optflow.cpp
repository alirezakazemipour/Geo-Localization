#include "optflow.h"



OptFlow::OptFlow(QObject *parent) : QObject(parent)
{
    needToInit = false;
    termcrit = TermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS, 20, 0.03);
}

void OptFlow::timerEvent(cv::Mat raw_image)
{
   std::cout<<"OPT "<<QThread::currentThreadId()<<std::endl;
    d.start();
    raw_image.copyTo(colorframe);
    cvtColor(colorframe, grayframe, CV_BGR2GRAY);
    OptFlow_LK();

}

void OptFlow::OptFlow_LK()
{
    // qDebug()<<"opt !!";
    // std::cout<<"we are here";

    if( needToInit )
    {
        goodFeaturesToTrack(grayframe, points[1], MAX_COUNT, 0.01, 10, Mat(), 3, 0, 0.04);
        cornerSubPix(grayframe, points[1], subPixWinSize, Size(-1,-1), termcrit);
    }
    else if( !points[0].empty() )
    {
        vector<uchar> status;
        vector<float> err;
        if(prevGray.empty())
            grayframe.copyTo(prevGray);
        calcOpticalFlowPyrLK(prevGray, grayframe, points[0], points[1], status, err, winSize,
                3, termcrit, 0, 0.001);



        Features_counter =0;
        delta_x = 0;
        delta_y = 0;

        for( size_t i = 0 ; i < points[1].size(); i++ )
        {
            if( status[i] )
            {
                points[1][Features_counter++] = points[1][i];
#ifdef _GRAPH
                line(colorframe, points[0][i], points[1][i], Scalar(0,255,0), 1, 8, 0);
#endif
                Point2f p1 = points[0][i], p2 = points[1][i];
                delta_x += (p1.x - p2.x);
                delta_y += (p1.y - p2.y);
            }
        }
qDebug()<<"Before division 1";
        delta_x /= (Features_counter);
qDebug()<<"After division1";
        delta_y /= (Features_counter);
qDebug()<<"Afetr division2";


        points[1].resize(Features_counter);
#ifdef _Serial
        //  transmiter->Fill_Data(2,(int)(delta_x *10),(int)(delta_y *10));
        //qDebug()<<"first = "<<(int)(delta_x *10);
        //qDebug()<<"sec = "<<(int)(delta_y *10);

        dx=int(delta_x*10);
        dy=int(delta_y*10);
        emit optSig(dx,dy);

#endif

    }


    if(points[1].size() < (unsigned int)THRESH_REFRESH)
        needToInit = true;
    else
        needToInit = false;

    //#ifdef _GRAPH
    //  imshow("LK Demo", colorframe);
    //#endif
   // std::cout<<"Delay"<< d.elapsed()<<std::endl;
    // waitKey(2);

    std::swap(points[1], points[0]);
    cv::swap(prevGray, grayframe);
}





OptFlow::~OptFlow()
{
    //    delete ui;
}
