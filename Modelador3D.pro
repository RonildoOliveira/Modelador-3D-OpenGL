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


LIBS += -lGLU -lglut


SOURCES += main.cpp\
        mainwindow.cpp \
    bib/glwidget.cpp \
    bib/Camera.cpp \
    bib/CameraDistante.cpp \
    bib/CameraJogo.cpp \
    bib/Desenha.cpp \
    bib/Vetor3D.cpp

HEADERS  += mainwindow.h \
    bib/glwidget.h \
    bib/Camera.h \
    bib/CameraDistante.h \
    bib/CameraJogo.h \
    bib/Desenha.h \
    bib/Vetor3D.h

FORMS    += mainwindow.ui


