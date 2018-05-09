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

void Torus::addSlices()
{
    this->slices++;
}

void Torus::addStacks()
{
    this->stacks++;
}

void Torus::decSlices()
{
    this->slices--;
}

void Torus::decStacks()
{
    this->stacks--;
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
        if(isEixo()){
            Desenha::drawEixos( 0.5 );
        }
         //glColor3d(0,1,0);
        //desenhando objeto
          if(isSelecionado()){
              glColor3f(0.22,1.0,0.07);
          }
          else{
              glColor3f(0.5,0.5,0.5);
          }

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

bool Torus::isSelecionado(){
    return this->selecionado;
}

void Torus::setEixo(bool eixo)
{
    this->eixo = eixo;
}

bool Torus::isEixo()
{
    return this->eixo;
}


void Torus::setSelecionado(bool selecionado){
    this->selecionado = selecionado;
}
