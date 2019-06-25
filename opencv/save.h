#pragma once

#include <opencv2/highgui/highgui_c.h>

#define  CV_GET_WHEEL_DELTA(flags)   ((short)((flags >> 16) & 0xffff)) 

#define  cvAddSearchPath(path) 

#define  cvvAddSearchPath   cvAddSearchPath 

#define  cvvCreateTrackbar   cvCreateTrackbar 

#define  cvvDestroyWindow   cvDestroyWindow 

#define  cvvInitSystem   cvInitSystem 

#define  cvvNamedWindow   cvNamedWindow 

#define  cvvResizeWindow   cvResizeWindow 

#define  cvvShowImage   cvShowImage 

#define  cvvWaitKey(name)   cvWaitKey(0) 

#define  cvvWaitKeyEx(name, delay)   cvWaitKey(delay) 

#define  HG_AUTOSIZE   CV_WINDOW_AUTOSIZE 

#define  set_postprocess_func   cvSetPostprocessFuncWin32 

#define  set_preprocess_func   cvSetPreprocessFuncWin32 
typedef void(*CvButtonCallback) (int state, void* userdata);

typedef void(*CvMouseCallback) (int event, int x, int y, int flags, void* param);

typedef void(*CvOpenGlDrawCallback) (void* userdata);

typedef void(*CvTrackbarCallback) (int pos);

typedef void(*CvTrackbarCallback2) (int pos, void* userdata);
