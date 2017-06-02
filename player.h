#ifndef SQUARE_H
#define SQUARE_H

#include <QtOpenGL/QGLWidget>
#include "figure.h"

class Square : public Figure
{
    //int _x;
    //int _y;
    int translate;
    int width;
    int height;
    QVector3D position;

    void rePosition(int x, int y);

public:

    int x();
    int y();

    //Square(double *v1, double *v2, double *v3, double *v4);
    Square(int x, int y, int w, int h);
    void draw();
    bool move();
    void moveLeft(int w);
    void moveRight(int w);

    int life;

public slots:
    //void moveLeft();
    //void moveRight();
};


#endif // SQUARE_H
