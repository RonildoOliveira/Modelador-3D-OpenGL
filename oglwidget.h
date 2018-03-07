#ifndef OGLWIDGET_H
#define OGLWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>

#include <GL/glut.h>

class OGLWidget : public QOpenGLWidget
{
public:
    OGLWidget(QWidget *parent = 0);   
    void add15();    
    ~OGLWidget();

public slots:
    void buttonPressEvent();
    void keyPressEvent(QKeyEvent *event);

private:

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
};

#endif // OGLWIDGET_H
