#include "teapot.h"
#include <iostream>

using namespace std;

Teapot::Teapot(){ cout<<"Solid Teapot"; }

void Teapot::desenha()
{
    //sistema local
    glPushMatrix();
        //composicao de transformacoes
        glTranslated(this->getTX(),this->getTY(),this->getTZ());

        glRotated(this->getAX(),0,0,1);
        glRotated(this->getAY(),0,1,0);
        glRotated(this->getAZ(),1,0,0);

        glScaled(this->getSX(),this->getSY(),this->getSZ());

        //desenhando eixos do sistema de coordenadas local 1
        Desenha::drawEixos( 0.5 );

        //desenhando objeto
        glColor3d(1,0,0);
        //glColor3d(0,0,1);
        //glColor3f(1,0.6,0);

        glutSolidTeapot(this->getSize());
    glPopMatrix();
}

float Teapot::getAX(){
    return this->ax;
}

void Teapot::addAX(float ax){
    this->ax += ax;
}

float Teapot::getAY(){
    return this->ay;
}

void Teapot::addAY(float ay){
    this->ay += ay;
}

float Teapot::getAZ(){
    return this->az;
}

float Teapot::getSize()
{
    return this->size;
}

void Teapot::setSize(float size)
{
    this->size = size;
}

void Teapot::addAZ(float az){
    this->az += az;
}

float Teapot::getTX()
{
    return this->tx;
}

float Teapot::getTY()
{
    return this->ty;
}

float Teapot::getTZ()
{
    return this->tz;
}

void Teapot::addTX(float tx)
{
    this->tx+=tx;
}

void Teapot::addTY(float ty)
{
    this->ty+=ty;
}

void Teapot::addTZ(float tz)
{
    this->tz+=tz;
}

float Teapot::getSX()
{
    return this->sx;
}

float Teapot::getSY()
{
    return this->sy;
}

float Teapot::getSZ()
{
    return this->sz;
}
