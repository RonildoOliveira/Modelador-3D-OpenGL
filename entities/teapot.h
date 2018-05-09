#ifndef TEAPOT_H
#define TEAPOT_H

#include <GL/glut.h>
#include <bib/CameraDistante.h>
#include <bib/Desenha.h>

#include<entities/model.h>

class Teapot : public Model {
public:
    Teapot();
    Teapot(float tx, float ty, float tz,
           float ax, float ay, float az,
           float sx, float sy, float sz);
    void desenha();

    float getAX();
    float getAY();
    float getAZ();

    float getSize();
    void  setSize(float size);

    void addAX(float ax) override;
    void addAY(float ay) override;
    void addAZ(float az) override;

    void addSX(float sx) override;
    void addSY(float sy) override;
    void addSZ(float sz) override;

    float getSX() override;
    float getSY() override;
    float getSZ() override;

    float getTX();
    float getTY();
    float getTZ();

    void addTX(float tx) override;
    void addTY(float ty) override;
    void addTZ(float tz) override;

    void addSlices() override;
    void addStacks() override;
    void decSlices() override;
    void decStacks() override;

    int getSlices() override;
    int getStacks() override;

    void setSelecionado(bool selecionado) override;
    bool isSelecionado() override;

    void setEixo(bool eixo) override;
    bool isEixo() override;

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

    bool selecionado = false;
    bool eixo = true;
};

#endif // TEAPOT_H
