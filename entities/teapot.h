#ifndef TEAPOT_H
#define TEAPOT_H

#include <GL/glut.h>
#include <bib/CameraDistante.h>
#include <bib/Desenha.h>

#include<entities/model.h>

class Teapot : public Model {
public:
    Teapot();
    void desenha();

    float getAX();
    float getAY();
    float getAZ();

    float getSize();
    void  setSize(float size);

    void addAX(float ax) override;
    void addAY(float ay) override;
    void addAZ(float az) override;

    float getTX();
    float getTY();
    float getTZ();

    void addTX(float tx) override;
    void addTY(float ty) override;
    void addTZ(float tz) override;

    float getSX();
    float getSY();
    float getSZ();

private:
    float size = 1.0;

    float trans_obj = false;

    float tx = 0.0;
    float ty = 0.0;
    float tz = 0.0;

    float ax = 0.0;
    float ay = 0.0;
    float az = 0.0;

    float delta = 5.0; //remover ou nao

    float sx = 1.0;
    float sy = 1.0;
    float sz = 1.0;
};

#endif // TEAPOT_H
