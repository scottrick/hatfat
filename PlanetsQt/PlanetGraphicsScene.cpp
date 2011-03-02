#include "PlanetGraphicsScene.h"

#include <QDateTime>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QLabel>
#include <QPaintEngine>
#include <QPainter>
#include <QPlastiqueStyle>
#include <QVBoxLayout>
#include <QDialog>

#include "GraphicsView.h"
#include "Noise.h"
#include "PlanetProgramOne.h"
#include "RoamMesh.h"
#include "ShaderManager.h"
#include "SimpleMeshData.h"
#include "ZCamera.h"""

#include <ctime>
#include <iostream>
using namespace std;

PlanetGraphicsScene::PlanetGraphicsScene(GraphicsView *pGraphicsView, QObject *parent) :
        QGraphicsScene(parent)
{
    m_pGraphicsView = pGraphicsView;

    //setup a FPS dialog window
    m_pFpsLabel = new QLabel(tr("FPS:"));
    m_pSeedLabel = new QLabel(tr("seed:"));

    QWidget *stats = createWidget(tr("stats"));
    stats->layout()->addWidget(m_pFpsLabel);
    stats->layout()->addWidget(m_pSeedLabel);

    addWidget(stats);

    //now that we have added all the windows we want, go through them all and position them correctly
    QPointF pos(10, 10);

    foreach (QGraphicsItem *item, items())
    {
        item->setFlag(QGraphicsItem::ItemIsMovable);
        item->setCacheMode(QGraphicsItem::DeviceCoordinateCache);

        const QRectF rect = item->boundingRect();
        item->setPos(pos.x() - rect.x(), pos.y() - rect.y());
        pos += QPointF(0, 10 + rect.height());
    }

    initialize();
}

QDialog *PlanetGraphicsScene::createDialog(const QString &windowTitle) const
{
    QDialog *dialog = new QDialog(0, Qt::CustomizeWindowHint | Qt::WindowTitleHint);

    dialog->setWindowOpacity(0.2);
    dialog->setWindowTitle(windowTitle);
    dialog->setLayout(new QVBoxLayout);

    return dialog;
}

void PlanetGraphicsScene::createRandomNoise()
{
    fTime = 0.0f;

    if (pTestNoise)
    {
        delete pTestNoise;
    }

    if (pTestData)
    {
        delete pTestData;
    }

    pTestNoise = new Noise(rand());
    pTestData = new SimpleMeshData(pTestNoise);

    QString numPart;
    numPart.setNum(pTestNoise->getSeed());
    m_pSeedLabel->setText(tr("seed: ") + numPart);
}

QWidget *PlanetGraphicsScene::createWidget(const QString &widgetTitle) const
{
    QWidget *widget = new QWidget(0, Qt::CustomizeWindowHint | Qt::WindowTitleHint);

    widget->setStyle(new QPlastiqueStyle());
    widget->setWindowOpacity(0.5);
    widget->setWindowTitle(widgetTitle);
    widget->setLayout(new QVBoxLayout());

    return widget;
}

void PlanetGraphicsScene::drawBackground(QPainter *painter, const QRectF &)
{
    //check for opengl errors
    GLenum error = glGetError();
    while (error != GL_NO_ERROR)
    {
        cout << "error: " << hex << error << dec << endl;
        error = glGetError();
    }

    ShaderManager::get().GetPlanetProgram()->SetPlanet(pPlanet);

    if (painter->paintEngine()->type() != QPaintEngine::OpenGL && painter->paintEngine()->type() != QPaintEngine::OpenGL2)
    {
        cout << "PaintEnginer of incorrect type! (type " << painter->paintEngine()->type() << ")" << endl;
        return;
    }

    if (bMultisampling)
    {
        glEnable(GL_MULTISAMPLE);
    }
    else
    {
        glDisable(GL_MULTISAMPLE);
    }

    if (bDepth)
    {
        glEnable(GL_DEPTH_TEST);
    }
    else
    {
        glDisable(GL_DEPTH_TEST);
    }

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    ZCamera::doTempPerspectiveCrap((float)width() / (float)height());
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
    glPushMatrix();

    switch (currentMode)
    {
    case SHADER:
        drawScene();
        break;

    case NOISE_TEST:
        drawNoise();
        break;
    }

    ++m_fpsCounter;

    glPopMatrix();
}

void PlanetGraphicsScene::drawNoise()
{
    glPushMatrix();

    ZCamera::doTempCameraCrap(g_fCameraDistance);
    glMultMatrixf(rotation.m);

    glLineWidth(1.0f);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

    glVertexPointer(3, GL_FLOAT, 0, pTestData->getVertices());
    glColorPointer(4, GL_UNSIGNED_BYTE, 0, pTestData->getColors());

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glDrawElements(GL_LINES, pTestData->getNumberOfIndices(), GL_UNSIGNED_INT, pTestData->getIndices());
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

    glLineWidth(4.0f);

    glBegin(GL_LINES);
    glColor4f(0.7f, 0.0f, 0.0f, 1.0f);
    glVertex3f(-20.0f, 0.0f, 0.0f);
    glVertex3f(20.0f, 0.0f, 0.0f);
    glColor4f(0.0f, 0.0f, 0.7f, 1.0f);
    glVertex3f(0.0f, 20.0f, 0.0f);
    glVertex3f(0.0f, -20.0f, 0.0f);
    glColor4f(0.0f, 0.7f, 0.0f, 1.0f);

    //draw x hash marks
    for (int i = -20; i <= 20; ++i)
    {
        glVertex3f((float) i, 0.25f, 0.0f);
        glVertex3f((float) i, -0.25f, 0.0f);
    }

    //draw y hash marks
    for (int i = -20; i <= 20; ++i)
    {
        glVertex3f(0.25f, (float) i, 0.0f);
        glVertex3f(-0.25f, (float) i, 0.0f);
    }

    glEnd();

    glPopMatrix();
}

void PlanetGraphicsScene::drawScene()
{
    glPushMatrix();

    ZCamera::doTempCameraCrap(g_fCameraDistance);
    glMultMatrixf(rotation.m);

//    ShaderManager::get().GetActiveProgram()->Activate();

    pRoamMesh->Render();

    glUseProgram(0);

    glPopMatrix();
}

void PlanetGraphicsScene::initialize()
{
    bFullscreen = false;
    bDepth = true;
    bMultisampling = true;

    pTestNoise      = 0;
    pTestData       = 0;

    m_fpsCounter = 0;
    m_lastTimeUpdate = QDateTime::currentMSecsSinceEpoch();

    initializeNoise();

    pPlanet = new Planet();
    pPlanet->Randomize();

    pRoamMesh = new RoamMesh();

    fTime = 0.0f;

    currentShape        = SPHERE;
    currentMode         = SHADER;
    bPaused             = true;

    PLANET_RADIUS       = 1.0f;
    MAX_CAMERA_DISTANCE = PLANET_RADIUS * 20.0f;
    MIN_CAMERA_DISTANCE = PLANET_RADIUS * 1.1f;
    g_fCameraDistance   = PLANET_RADIUS * 2.5f;
}

void PlanetGraphicsScene::initializeNoise()
{
    srand(time(0));
    createRandomNoise();
}

void PlanetGraphicsScene::keyPressEvent(QKeyEvent *pKeyEvent)
{
    //cout << "key=" << pKeyEvent->key() << endl;

    switch (pKeyEvent->key())
    {
    case '1':
        currentMode = SHADER;
        break;

    case '2':
        currentMode = NOISE_TEST;
        break;

    case 112: // 'p' and 'P'
    case 80:
        bPaused = !bPaused;
        break;

    case 45: // -
    case 95: // _
        g_fCameraDistance = 1.03f * g_fCameraDistance;
        g_fCameraDistance = min(g_fCameraDistance, MAX_CAMERA_DISTANCE);
        break;

    case 61: // =
    case 43: // +
        g_fCameraDistance = 0.98f * g_fCameraDistance;
        g_fCameraDistance = max(g_fCameraDistance, MIN_CAMERA_DISTANCE);
        break;

    case 'C':
    case 'c': //CTRL + C to quit
        if (pKeyEvent->modifiers() == Qt::ControlModifier)
        {
            exit(1);
        }
        break;
    case 'f':
    case 'F':
        if (bFullscreen)
        {
            m_pGraphicsView->move(80, 60);
            m_pGraphicsView->resize(800, 600);
        }
        else
        {
            m_pGraphicsView->showFullScreen();
        }

        bFullscreen = !bFullscreen;
        break;
    case 46: // '>' and '.'
    case 62:
        ShaderManager::get().NextProgram();
        break;

    case 44: // '<' and ",'
    case 60:
        ShaderManager::get().PrevProgram();
        break;

    case 91: // '[' and '{'
    case 123:
        prevShape();
        break;

    case 93: // ']' and '}'
    case 125:
        nextShape();
        break;

    case 'd':
    case 'D':
        bDepth = !bDepth;
        break;

    case 'm':
    case 'M':
        bMultisampling = !bMultisampling;
        break;

//    case '3':
//        pRoamMesh->testIndex++;
//        if (pRoamMesh->testIndex > 11)
//        {
//            pRoamMesh->testIndex = 11;
//        }
//        break;

//        case '4':
//        pRoamMesh->testIndex--;
//        if (pRoamMesh->testIndex < 0)
//        {
//            pRoamMesh->testIndex = 0;
//        }
//        break;

    case 32: //spacebar
        createRandomNoise();
        pPlanet->Randomize();
        break;

    default:

        break;
    }
}

void PlanetGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *pMouseEvent)
{
    QGraphicsScene::mouseMoveEvent(pMouseEvent);

    if (pMouseEvent->isAccepted())
    {
        return;
    }

    if (pMouseEvent->buttons() & Qt::LeftButton) {
        const QPointF delta = pMouseEvent->scenePos() - pMouseEvent->lastScenePos();

        Vector3 axis = Vector3(-delta.y(), -delta.x(), 0.0f);
        Matrix rot = Matrix();
        rot.SetRotation(axis, sqrt((float)abs(delta.x()) + (float)abs(delta.y())));

        rotation.RotateBy(rot);

        pMouseEvent->accept();
    }
}

void PlanetGraphicsScene::nextShape()
{
    if (currentShape + 1 < LAST_SHAPE)
    {
        currentShape = (SHAPE) (currentShape + 1);
    }
}

void PlanetGraphicsScene::prevShape()
{
    if (currentShape > 0)
    {
        currentShape = (SHAPE) (currentShape - 1);
    }
}

void PlanetGraphicsScene::refresh()
{
    if (!bPaused)
    {
        pTestData->generateMeshForTime(fTime);
        fTime += 0.003f;
    }

    qint64 currentTime = QDateTime::currentMSecsSinceEpoch();

    if (currentTime - m_lastTimeUpdate > 1000)
    {
        m_lastTimeUpdate += 1000;

        QString num;
        num.setNum(m_fpsCounter);
        m_pFpsLabel->setText(num + tr(" fps"));
        m_fpsCounter = 0;
    }
}
