#include <QtGui/QApplication>
#include <QApplication>

#include "GLWidget.h"

bool        bApplicationRunning     = true;
GLWidget    *pGLWidget              = 0;

void refreshAll();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    pGLWidget = new GLWidget();
    pGLWidget->show();

    while (bApplicationRunning)
    {
        a.processEvents();
        refreshAll();

        pGLWidget->updateGL();
    }

//    return a.exec();
}

void refreshAll()
{
    pGLWidget->refresh();
}
