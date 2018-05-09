#include <QKeyEvent>
#include <QMessageBox>

#include <iostream>

#include "oglwidget.h"

#include "entities/model.h"
#include "entities/torus.h"
#include "entities/teapot.h"


OGLWidget::OGLWidget(QWidget *parent)
    : QGLWidget(parent)
{
    connect( &timer, SIGNAL(timeout()), this, SLOT(updateGL()) );
    timer.start(16);
}

void OGLWidget::initializeGL()
{
    glClearColor(1,1,1,1);

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

    if(listaModelos.size() > 0){
        for (int index = 0; index < listaModelos.size(); ++index) {
            listaModelos.at(index)->desenha();
        }
    }

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
        case Qt::Key_Right:{
            if(!listaModelos.empty()){
                if(cont == -1){
                    cont++;
                    (listaModelos[cont])->setSelecionado(true);
                }else if(cont >= 0 && (cont < (listaModelos.size() - 1))){
                    (listaModelos[cont])->setSelecionado(false);
                    cont++;
                    (listaModelos[cont])->setSelecionado(true);
                }else{
                    (listaModelos[cont])->setSelecionado(false);
                    cont = -1;
                }
            }
        }
        break;

        case Qt::Key_E:{
            if(!listaModelos.empty()){
                if((listaModelos[cont])->isSelecionado()){
                    (listaModelos[cont])->setEixo(!(listaModelos[cont])->isEixo());
                }
            }
        }
        break;

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
            if(!listaModelos.empty()){
                if (listaModelos.at(cont)->getSlices() > 3 && listaModelos.at(cont)->getStacks() > 3)
                {
                    listaModelos.at(cont)->addSlices();
                    listaModelos.at(cont)->addStacks();
                }
            }
            break;

        case Qt::Key_Minus:
        case Qt::Key_N:
            if(!listaModelos.empty()){
                if (listaModelos.at(cont)->getSlices() > 3 && listaModelos.at(cont)->getStacks() > 3)
                {
                    listaModelos.at(cont)->decSlices();
                    listaModelos.at(cont)->decStacks();
                }
            }
            break;

        case Qt::Key_R:
            if(!listaModelos.empty()){
                listaModelos.erase (listaModelos.begin()+cont);
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
    float fator = 10.0;

    int x = event->x();
    int y = event->y();

    int lx = lastPos.x();
    int ly = lastPos.y();

    if(!listaModelos.empty()){
        if (event->buttons() & Qt::LeftButton) {
            listaModelos.at(cont)->addAX(0.1*(y - ly));
            listaModelos.at(cont)->addAY(0.1*(x - lx));

        } else if (event->buttons() & Qt::RightButton) {
            listaModelos.at(cont)->addTX(0.01*(x - lx));
            listaModelos.at(cont)->addTY(-0.01*(y - ly));
        }
    }

     fator = 1000.0;
    if (event->buttons() & Qt::LeftButton && event->buttons() & Qt::RightButton) {
        if (!trans_obj) {
            cam->zoom(y,ly);
        } else {
            listaModelos.at(cont)->addTZ((y - ly)/fator);
            fator = 100.0;
            listaModelos.at(cont)->addAZ((x - lx)/fator);
        }
    }

    lastPos = event->pos();
}

void OGLWidget::addTorusListaModelos()
{
    this->listaModelos.push_back(new Torus());
}

void OGLWidget::addTeapotListaModelos()
{
    this->listaModelos.push_back(new Teapot());
}

void OGLWidget::increaseCont()
{
    this->cont++;
}

void OGLWidget::decreaseCont()
{
    this->cont--;
}

OGLWidget::~OGLWidget()
{

}
