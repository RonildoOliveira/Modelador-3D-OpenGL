#ifndef MODEL_H
#define MODEL_H

#include <GL/glut.h>
#include <bib/CameraDistante.h>
#include <bib/Desenha.h>

/** Classe Abstrata **/
class Model
{
public:
    Model();
    virtual void desenha() = 0;
    /*
    virtual void addStacks() = 0;
    virtual void addSlices() = 0;

    virtual int addSlices(int slice) = 0;
    virtual int addStacks(int stack) = 0;

    virtual void addAX(float ax) = 0;
    virtual void addAY(float ay) = 0;
    virtual void addAZ(float az) = 0;

    virtual float getTX() = 0;
    virtual float getTY() = 0;
    virtual float getTZ() = 0;

    virtual int getSlices() = 0;
    virtual int getStacks() = 0;

    virtual void addTX(float tx) = 0;
    virtual void addTY(float ty) = 0;
    virtual void addTZ(float tz) = 0;
    */
};

#endif // MODEL_H
