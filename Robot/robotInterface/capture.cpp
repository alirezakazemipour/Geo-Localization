#include "capture.h"

capture::capture(QObject *parent) : QObject(parent)
{

    down_cam.open(DOWN_CAM_NUM);
    if( down_cam.isOpened() )
    {
        down_cam.set(CV_CAP_PROP_FPS, DOWN_FPS);
        down_cam.set(CV_CAP_PROP_FRAME_WIDTH, FRAME_WIDTH);
        down_cam.set(CV_CAP_PROP_FRAME_HEIGHT, FRAME_HEIGHT);
        down_cam >> down_frame ;



    }
    else
    {
        qDebug()<<"could not open down_cam\n";
        exit(0);
    }
    


}


void capture::downFrame_ready()
{
    qDebug()<<"CAM Thread"<<thread()->currentThreadId();

    down_cam >> down_frame ;

    opt_frame = down_frame.clone();

    emit down_image_opt(opt_frame);

    emit down_image_send(down_frame);
    
}





