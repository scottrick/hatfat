#include "ZCamera.h"

//#include "hatfat/glee/GLee.h"

#include "GL/glu.h"

ZCamera::ZCamera()
{

}

void ZCamera::doTempCameraCrap(float fCameraDistance)
{
    gluLookAt(0.0, 0.0, fCameraDistance, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void ZCamera::doTempPerspectiveCrap(float ratio)
{
    gluPerspective(60.0, ratio, 0.1, 100.0);
}
