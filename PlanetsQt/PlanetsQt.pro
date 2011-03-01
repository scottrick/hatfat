#-------------------------------------------------
#
# Project created by QtCreator 2010-10-02T10:34:13
#
#-------------------------------------------------

QT       += core gui
QT       += opengl

TARGET = PlanetsQt

CONFIG += console

//DEFINES += GLEW_BUILD=GLEW_STATIC
//DEFINES += GLEW_STATIC

//INCLUDEPATH += -L../../hatfat/include

//win32:LIBS += d:/scott/projects/planetsqt/planetsqt/hatfat/lib/glew32.lib
//win32:LIBS += d:/scott/projects/planetsqt/planetsqt/hatfat/lib/glew32s.lib
//win32:LIBS += -L../../hatfat/lib/glew32.lib
//win32:LIBS += -L../../hatfat/lib/glew32s.lib
//win32:LIBS += -L../../hatfat/bin/glew32.dll
//LIBS += -Lglew32.dll
//LIBS += -Ld:/scott/projects/planetsqt/planetsqt/glew32.dll
//LIBS += -Lglew32s.lib

TEMPLATE = app
\
SOURCES += main.cpp\
    VertexShader.cpp \
    Vector3.cpp \
    Unknown.cpp \
    ToonProgram.cpp \
    TestTextureProgram.cpp \
    StripeProgram.cpp \
    SimpleMeshData.cpp \
    ShaderProgram.cpp \
    ShaderManager.cpp \
    Shader.cpp \
    PlanetProgramOne.cpp \
    PlanetOptions.cpp \
    Planet.cpp \
    Options.cpp \
    Noise.cpp \
    Matrix.cpp \
    FragmentShader.cpp \
    CubeProgram.cpp \
    BrickProgram.cpp \
    hatfat/glee/GLee.c \
    GraphicsView.cpp \
    PlanetGraphicsScene.cpp \
    ZVertex.cpp \
    ZVertexArray.cpp \
    RoamMesh.cpp \
    ZTriangle.cpp \
    ZDiamond.cpp \
    ZCamera.cpp

HEADERS  += \
    VertexShader.h \
    Vector3.h \
    Unknown.h \
    ToonProgram.h \
    TestTextureProgram.h \
    StripeProgram.h \
    SimpleMeshData.h \
    ShaderProgram.h \
    ShaderManager.h \
    Shader.h \
    PlanetProgramOne.h \
    PlanetOptions.h \
    Planet.h \
    Options.h \
    Noise.h \
    Matrix.h \
    FragmentShader.h \
    def.h \
    CubeProgram.h \
    BrickProgram.h \
    hatfat/glee/GLee.h \
    GraphicsView.h \
    PlanetGraphicsScene.h \
    ZVertex.h \
    ZVertexArray.h \
    RoamMesh.h \
    ZTriangle.h \
    ZDiamond.h \
    ZCamera.h

FORMS    +=

RESOURCES += \
    resources.qrc
