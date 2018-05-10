#-------------------------------------------------
#
# Project created by QtCreator 2018-03-06T00:14:05
#
#-------------------------------------------------

QT       += core gui
QT       += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Modelador3D
TEMPLATE = app

DEFINES += USE_SDL
LIBS += -lglut -l3ds -lGLU -lGL -lm -lSDL -lSDL_image

SOURCES += main.cpp \
    entities/torus.cpp \
    entities/model.cpp \
    entities/teapot.cpp \
    entities/models/objmodelloader.cpp \
    entities/cube.cpp \
    entities/models/tdsmodelloader.cpp

SOURCES += mainwindow.cpp \
    bib/Camera.cpp \
    bib/CameraDistante.cpp \
    bib/CameraJogo.cpp \
    bib/Desenha.cpp \
    bib/Vetor3D.cpp \
    oglwidget.cpp


HEADERS  += mainwindow.h \
    bib/Camera.h \
    bib/CameraDistante.h \
    bib/CameraJogo.h \
    bib/Desenha.h \
    bib/Vetor3D.h \
    oglwidget.h \
    entities/torus.h \
    entities/model.h \
    entities/teapot.h \
    entities/models/objmodelloader.h \
    entities/cube.h \
    entities/models/tdsmodelloader.h

FORMS    += mainwindow.ui

DISTFILES += \
    README.md


