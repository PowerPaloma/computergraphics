#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QtOpenGL/QGLWidget>
#include "figure.h"
#include "glwidget.h"

class Enemy : public Figure
{

    //int _x;
    //int _y;
    int translate;
    int width;
    int height;
    int widthWind;
    QVector3D position;
    int heightWind;
    GLWidget *widget;
    float r;
    float g;
    float b;
    int tempo;

    void rePosition(int x, int y);
public:

    int x();
    int y();

    //Square(double *v1, double *v2, double *v3, double *v4);
    Enemy(int x, int y, int w, int h, int width, GLWidget *widget);
    void draw();
    bool move();

public slots:
    //void chamaEnemy();
    //void moveRight();

signals:
    QString uhuu(QString str);
};
#endif // ENEMY_H
