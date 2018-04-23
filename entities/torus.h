#ifndef TORUS_H
#define TORUS_H

#include <GL/glut.h>

#include <bib/CameraDistante.h>
#include <bib/Desenha.h>

#include <entities/model.h>

class Torus : public Model
{
public:
    Torus();
    void desenha();

    float getAX();
    float getAY();
    float getAZ();

    void addAX(float ax);
    void addAY(float ay);
    void addAZ(float az);

    void addTX(float tx);
    void addTY(float ty);
    void addTZ(float tz);

    float getSX();
    float getSY();
    float getSZ();

    int addSlices(int slice);
    int addStacks(int stack);

    int getSlices();
    int getStacks();

private:
    int slices = 10;
    int stacks = 10;

    float trans_obj = false;

    float tx = 0.0;
    float ty = 0.0;
    float tz = 0.0;

    float ax = 0.0;
    float ay = 0.0;
    float az = 0.0;

    float delta = 5.0;

    float sx = 1.0;
    float sy = 1.0;
    float sz = 1.0;
};

#endif // TORUS_H
