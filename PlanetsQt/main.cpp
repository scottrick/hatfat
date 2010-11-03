#include <QtGui/QApplication>
#include <QApplication>

#include "GLWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GLWidget glWidget;
    glWidget.show();

    return a.exec();
}
