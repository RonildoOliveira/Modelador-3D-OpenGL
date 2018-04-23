#include <QKeyEvent>
#include <QMessageBox>

#include <iostream>
#include <vector>

#include "oglwidget.h"
#include "entities/torus.h"

using namespace  std;

vector<Model*> listaModelos;
Torus * torus;

OGLWidget::OGLWidget(QWidget *parent)
    : QGLWidget(parent)
{
    connect( &timer, SIGNAL(timeout()), this, SLOT(updateGL()) );
    timer.start(16);
}

void OGLWidget::initializeGL()
{
    torus = new Torus();
    listaModelos.push_back(torus);

    glClearColor(1,1,1,1);
    //glClearColor(0.3,0.3,0.3,1.0);

    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
    glEnable(GL_NORMALIZE); //mantem a qualidade da iluminacao mesmo quando glScalef eh usada

    glShadeModel(GL_SMOOTH);
    //glShadeModel(GL_FLAT);

    glEnable(GL_DEPTH_TEST);

//    //definindo uma luz
        glEnable(GL_LIGHT0);

        const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
        const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
        const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

        const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
        const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
        const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
        const GLfloat high_shininess[] = { 100.0f };

        glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);

        glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
}

void OGLWidget::paintGL()
{
    displayInit();

    //sistema global
    glPushMatrix();
        //desenhando eixos do sistema de coordenadas global
          Desenha::drawEixos( 0.5 );
        //chao
        glColor3d(0.3,0.3,0.3);
        Desenha::drawGrid( 5, 0, 1, 1 );
    glPopMatrix();

    /*
    //sistema local 1
    glPushMatrix();
        //composicao de transformacoes
        glTranslated(tx,ty,tz);
        glRotated(az,0,0,1);
        glRotated(ay,0,1,0);
        glRotated(ax,1,0,0);
        glScaled(sx,sy,sz);
        //desenhando eixos do sistema de coordenadas local 1
          Desenha::drawEixos( 0.5 );
        //desenhando objeto
        glColor3d(1,0,0);
        //glColor3d(0,0,1);
        //glColor3f(1,0.6,0);
        glutSolidTorus(0.2,0.8,slices,stacks);
        //glutWireTorus(0.2,0.8,slices,stacks);
        //glutSolidTeapot(0.6);
        //glutWireTeapot(0.6);
        //Desenha::drawBox( 0.0,0.0,0.0, 1.0,1.0,1.0 );
        //Desenha::drawBox( -1.0,-1.0,-1.0, 1.0,1.0,1.0 );
    glPopMatrix();
    */
    torus->desenha();
    //listaModelos.at(0)->desenha();

    displayEnd();
}

void OGLWidget::displayInit()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    const float ar = height>0 ? (float) width / (float) height : 1.0;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30.,ar,0.1,1000.);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //definindo posicao e orientacao da camera
    //gluLookAt(0.0,1.0,15.0, 0.0,0.0,-1.0, 0.0,1.0,0.0);
    gluLookAt(cam->e.x,cam->e.y,cam->e.z, cam->c.x,cam->c.y,cam->c.z, cam->u.x,cam->u.y,cam->u.z);
}

void OGLWidget::displayEnd()
{

}

void OGLWidget::resizeGL(int w, int h)
{
    width = w;
    height = h;
}

void OGLWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_Escape:
        case Qt::Key_Return:
        case Qt::Key_Q:
            exit(0);
            break;

        case Qt::Key_T:
            trans_obj = !trans_obj;
            break;

        case Qt::Key_Plus:
        case Qt::Key_M:
            torus->addSlices(1);
            torus->addStacks(1);
            break;

        case Qt::Key_Minus:
        case Qt::Key_N:
            if (torus->getSlices() > 3 && torus->getStacks() > 3)
            {
                torus->addSlices(-1);
                torus->addStacks(-1);
            }
            break;

    }
}

void OGLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void OGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int x = event->x();
    int y = event->y();
    int lx = lastPos.x();
    int ly = lastPos.y();

//    int dx = x - lx;
//    int dy = y - ly;

    if (event->buttons() & Qt::LeftButton) {
        torus->addAX(0.1*(y - ly));
        torus->addAY(0.1*(x - lx));
        //ax += 0.1*(y - ly);
        //ay += 0.1*(x - lx);
    } else if (event->buttons() & Qt::RightButton) {
        torus->addTX(0.01*(x - lx));
        torus->addTY(-0.01*(y - ly));
        //tx += 0.01*(x - lx);
        //ty += -0.01*(y - ly);
    }

    lastPos = event->pos();
}

void OGLWidget::buttonPressEvent(){
    stacks--;
}

OGLWidget::~OGLWidget()
{

}