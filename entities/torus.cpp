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
}
