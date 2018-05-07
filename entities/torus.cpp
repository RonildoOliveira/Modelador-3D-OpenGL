#include "torus.h"

#include <iostream>

using namespace std;

Torus::Torus()
{
    cout << "Torus";
}

float Torus::getAX(){
    return this->ax;
}

void Torus::addAX(float ax){
    this->ax += ax;
}

float Torus::getAY(){
    return this->ay;
}

void Torus::addAY(float ay){
    this->ay += ay;
}

float Torus::getAZ(){
    return this->az;
}

void Torus::addAZ(float az){
    this->az += az;
}

void Torus::addTX(float tx)
{
    this->tx+=tx;
}

void Torus::addTY(float ty)
{
    this->ty+=ty;
}

void Torus::addTZ(float tz)
{
    this->tz+=tz;
}

float Torus::getSX()
{
    return this->sx;
}

float Torus::getSY()
{
    return this->sy;
}

float Torus::getSZ()
{
    return this->sz;
}

float Torus::getTX()
{
    return this->tx;
}

float Torus::getTY()
{
    return this->ty;
}

float Torus::getTZ()
{
    return this->tz;
}

int Torus::addSlices(int slice)
{
    this->slices+=slice;
}

int Torus::addStacks(int stack)
{
    this->stacks+=stack;
}

int Torus::getSlices()
{
    return this->slices;
}

int Torus::getStacks()
{
    return this->stacks;
}

void Torus::desenha(){
    //sistema local
    glPushMatrix();
        //composicao de transformacoes
        glTranslated(this->getTX(),this->getTY(),this->getTZ());

        glRotated(this->getAX(),0,0,1);
        glRotated(this->getAY(),0,1,0);
        glRotated(this->getAZ(),1,0,0);

        glScaled(this->getSX(),this->getSX(),this->getSZ());
        //desenhando eixos do sistema de coordenadas local 1
          Desenha::drawEixos( 0.5 );
        //desenhando objeto
        glColor3d(1,0,0);
        //glColor3d(0,0,1);
        //glColor3f(1,0.6,0);

        glutSolidTorus(this->getInnerRadius(),this->getOutterRadius(),
                       this->getSlices(),this->getStacks());
    glPopMatrix();
}

float Torus::getInnerRadius()
{
    return this->innerRadius;
}

float Torus::getOutterRadius()
{
    return this->outterRadius;
}

void Torus::setInnerRadius(float innerRadius)
{
    this->innerRadius = innerRadius;
}

void Torus::setOutterRadius(float outterRadius)
{
    this->outterRadius = outterRadius;
}
