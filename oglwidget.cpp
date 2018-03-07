#include <QKeyEvent>
#include <QMessageBox>

#include <iostream>

#include "oglwidget.h"

using namespace  std;

int angulo = 0;

OGLWidget::OGLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    connect( this, SIGNAL(timeout()), this, SLOT(updateGL()) );

}

OGLWidget::~OGLWidget()
{

}

void OGLWidget::initializeGL()
{
    glClearColor(0,0,0,1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
}

void OGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glRotatef(angulo,0,0,1);

    glBegin(GL_TRIANGLES);        
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(-0.5, -0.5, 0);
        glColor3f(0.0, 1.0, 0.0);
        glVertex3f( 0.5, -0.5, 0);
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f( 0.0,  0.5, 0);
    glEnd();
}

void OGLWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)w/h, 0.01, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,0,5,0,0,0,0,1,0);
}

void OGLWidget::buttonPressEvent(){
    angulo = 10;
    /*
    QMessageBox msgBox;
    msgBox.setText("The document has been modified.");
    msgBox.exec();
    */
}

void OGLWidget::keyPressEvent(QKeyEvent *event){
    switch (event->key())
        {
            case Qt::Key_Escape:
            case Qt::Key_Return:
            case Qt::Key_Q:
                exit(0);
                break;
        }

}
