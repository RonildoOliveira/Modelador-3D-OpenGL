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
        if(isEixo()){
            Desenha::drawEixos( 0.5 );
        }

        //desenhando objeto

        if(isSelecionado()){
            glColor3f(0.22,1.0,0.07);
        }
        else{
            glColor3f(0.5,0.5,0.5);
        }

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

bool Teapot::isSelecionado(){
    return this->selecionado;
}

void Teapot::setEixo(bool eixo)
{
    this->eixo = eixo;
}

bool Teapot::isEixo()
{
    return this->eixo;
}

void Teapot::setSelecionado(bool selecionado){
    this->selecionado = selecionado;
}

void Teapot::addSlices()
{

}

void Teapot::addStacks()
{

}

void Teapot::decSlices()
{

}

void Teapot::decStacks()
{

}


int Teapot::getSlices()
{
    return 0;
}

int Teapot::getStacks()
{
    return 0;
}
