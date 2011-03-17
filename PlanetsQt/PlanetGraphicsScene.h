#ifndef PLANETGRAPHICSSCENE_H
#define PLANETGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QtGlobal>

#include "Matrix.h"

class QKeyEvent;
class QLabel;
class QMouseEvent;
class QPainter;

class GraphicsView;
class Noise;
class Planet;
class SimpleMeshData;
class RoamMesh;

enum MODE { SHADER, NOISE_TEST };
enum SHAPE { SPHERE, TEAPOT, CONE, CUBE, DODECAHEDRON, ICOSAHEDRON, OCTAHEDRON, TETRAHEDRON, TORUS, LAST_SHAPE };

class PlanetGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit PlanetGraphicsScene(GraphicsView *pGraphicsView, QObject *parent = 0);

    bool        isFullscreen() { return bFullscreen; }

    void        drawBackground(QPainter *painter, const QRectF &);
    void        nextShape();
    void        prevShape();

    void        refresh();

protected:
    QDialog *createDialog(const QString &windowTitle) const;
    QWidget *createWidget(const QString &widgetTitle) const;

    void            keyPressEvent(QKeyEvent *pKeyEvent);

    void            mouseMoveEvent(QGraphicsSceneMouseEvent *pMouseEvent);

private:
    QLabel          *m_pFpsLabel;
    QLabel          *m_pSeedLabel;

    GraphicsView    *m_pGraphicsView;
    bool            bFullscreen;

    //opengl settings
    //opengl settings
    //opengl settings
    bool            bMultisampling;
    bool            bDepth;
    bool            bLight;

    bool            bPaused;
    float           fTime;
    Matrix          rotation;

    Noise           *pTestNoise;
    SimpleMeshData  *pTestData;
    Planet          *pPlanet;
    RoamMesh        *pRoamMesh;

    SHAPE           currentShape;
    MODE            currentMode;

    void            createRandomNoise();
    void            drawNoise();
    void            drawScene();
    void            initialize();
    void            initializeNoise();

    float           PLANET_RADIUS;
    float           MAX_CAMERA_DISTANCE;
    float           MIN_CAMERA_DISTANCE;
    float           g_fCameraDistance;

    int             m_fpsCounter;
    qint64          m_lastTimeUpdate;

signals:

public slots:

};

#endif // PLANETGRAPHICSSCENE_H
