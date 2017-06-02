#ifndef FIGURE_H
#define FIGURE_H

#include <QVector>
#include <QVector3D>

class Figure
{

protected:
    //QVector<QVector3D> vertices;
    //float translate;
public:
    QString nome;

    explicit Figure();
    ~Figure();
    virtual void draw();
    virtual bool move();
    QVector<QVector3D> vertices;
    //virtual void moveLeft();
    //virtual void moveRight();
};

#endif // FIGURE_H
