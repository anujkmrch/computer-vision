/**

Anuj Kumar Chaudhary <me@anujkch.com>
If you are using qt creator add the following line to include the opencv library in your project
CONFIG += link_pkgconfig
PKGCONFIG += opencv

if you are using plain gcc compiler use
gcc -o outputname sourcecode.c `pkg-config --cflags --libs opencv`
then execute by typing in terminal ./outputname

I am using ubuntu 16.04, gcc 5.4+, Opencv 2.4.9
if you are confused, how to install opencv in your Ubuntu 16.04 System
use my install script for Ubuntu 16.04 from https://anujkch.com/installer

Press any key to exit from the code
*/

#include <stdio.h>

#include "cv.h"
#include "highgui.h"
#include "opencv2/imgproc/imgproc_c.h"

#define CAMERAID 0

int main(void)
{

    IplImage * frame;
    CvCapture *camera = cvCreateCameraCapture(CAMERAID);

    const char *cascade_name = "./haarcascade_frontalface_default.xml";
    CvHaarClassifierCascade *cascade = 0;
    CvMemStorage *storage = 0;

    cascade = (CvHaarClassifierCascade *) cvLoad (cascade_name, 0, 0, 0);
    CvSeq *faces;

    IplImage *gray;
    int i,c;

    while(1){

        frame = cvQueryFrame(camera);

        cvFlip(frame,frame,1);

        if(!frame)

        {
            printf("Cannot get frame");
            break;
        }

        gray = cvCreateImage (cvGetSize(frame), IPL_DEPTH_8U, 1);
        cvCvtColor(frame,gray,CV_BGR2GRAY);

        storage = cvCreateMemStorage (0);
        cvClearMemStorage (storage);

        double t = (double)cvGetTickCount();

        faces = cvHaarDetectObjects(gray,cascade,storage,1.1,2,0,cvSize(30,30),cvSize(0,0));

        for (i = 0; i < (faces ? faces->total : 0); i++) {
             CvRect *r = (CvRect *) cvGetSeqElem (faces, i);
             cvRectangle(frame,cvPoint(r->x,r->y),cvPoint((r->x + r->width),(r->y+r->height)),cvScalar(0,255,0,0),1,8,0);
        }

        cvShowImage("Camera Input",frame);

        if( cvWaitKey( 10 ) >= 0 ){

            break;

        }

    }

    cvReleaseCapture(&camera);
    cvDestroyWindow("Camera Input");
    cvWaitKey(0);

    return 0;

}
