#include <QtGui/QApplication>
#include <QApplication>
#include <QGLWidget>
#include <QIcon>

#include "GraphicsView.h"
#include "PlanetGraphicsScene.h"

#include <iostream>
using namespace std;

bool                    bApplicationRunning     = true;
PlanetGraphicsScene     *pPlanetScene           = 0;

void refreshAll();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGLWidget glWidget(QGLFormat(QGL::SampleBuffers));
    pPlanetScene = new PlanetGraphicsScene();
    GraphicsView view;

    view.setWindowIcon(QIcon(":/planets/resources/icon.xpm"));

    view.setViewport(&glWidget);
    view.setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    view.setScene(pPlanetScene);

    view.showFullScreen();
//    view.show();
//    view.resize(800, 600);

    while (bApplicationRunning)
    {
        a.processEvents();
        refreshAll();

        pPlanetScene->update();
    }

    delete pPlanetScene;
}

void refreshAll()
{
    pPlanetScene->refresh();
}
