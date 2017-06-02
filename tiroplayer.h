#ifndef TIROPLAYER_H
#define TIROPLAYER_H

#include <QtOpenGL/QGLWidget>
#include "figure.h"
#include <QVector3D>

class QTimer;

class TiroPlayer : public Figure
{

    int width;
    int height;
    int screenHeight;  // Retirar isso, não esquecer disso nos métodos
    int translate; // O quanto vai subir

    QVector3D position;
    QTimer *t;

public:
    //TiroPlayer(double*, double*, double*, double*);
    TiroPlayer(int x, int y, int screenHeight);
    void draw();
    bool move();
    void shoot();
};

#endif // TIROPLAYER_H
