#include "player.h"
#include <iostream>
#include <QtOpenGL>
#include <GL/glu.h>
#include <QDebug>

//Square::Square(double *v1, double *v2, double *v3, double *v4)
Square::Square(int x, int y, int w, int h)
{    
    this->nome = "Jogador";

    this->translate = 30.0;
    this->position= QVector3D(x, y, 0); // posição inicial do player
    this->width = w;
    this->height = h;
    this->life = 3;

    // Criar os vértices
    this->vertices << QVector3D(this->position.x() - this->width/2, this->position.y() - this->height/2, 0.0) \
            << QVector3D(this->position.x() + this->width/2, this->position.y() - this->height/2, 0.0) \
            << QVector3D(this->position.x() + this->width/2, this->position.y() + this->height/2, 0.0) \
            << QVector3D(this->position.x() - this->width/2, this->position.y() + this->height/2, 0.0);
}

int Square::x()
{
    return this->position.x();
}

int Square::y()
{
    return this->position.y();
}

void Square::draw()
{
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glLoadIdentity();
    glColor3f(1.0,1.0,1.0);


    glPushMatrix();
    //glTranslatef(this->translate, 0.0, 0.0);

    glBegin(GL_QUADS);
    glVertex3d(this->vertices.at(0).x(), this->vertices.at(0).y(), this->vertices.at(0).z());
    glVertex3d(this->vertices.at(1).x(), this->vertices.at(1).y(), this->vertices.at(1).z());
    glVertex3d(this->vertices.at(2).x(), this->vertices.at(2).y(), this->vertices.at(2).z());
    glVertex3d(this->vertices.at(3).x(), this->vertices.at(3).y(), this->vertices.at(3).z());
    glEnd();
    glPopMatrix();
}

void Square::rePosition(int x, int y)
{
    //qDebug() << this->position.x() << " para " << x << " & " << this->position.y() << " para " << y;
    this->position.setX(x);
    this->position.setY(y);
    this->vertices.clear();
    this->vertices << QVector3D(this->position.x() - this->width/2, this->position.y() - this->height/2, 0.0) \
            << QVector3D(this->position.x() + this->width/2, this->position.y() - this->height/2, 0.0) \
            << QVector3D(this->position.x() + this->width/2, this->position.y() + this->height/2, 0.0) \
            << QVector3D(this->position.x() - this->width/2, this->position.y() + this->height/2, 0.0);
}

void Square::moveLeft(int w)
{
    int m = this->position.x() - this->translate;
    //qDebug() << "m = " << this->position.x() << " - " << this->translate << " ->" << m;
    if(m > -w/2)
    {
        this->rePosition(m, this->position.y());
    }
    /*QVector<QVector3D> vtx;
    QVector<QVector3D>::iterator it;
    for(it = this->vertices.begin(); it != this->vertices.end(); ++it)
    {
        if(it->x() - this->translate > -w/2)
            vtx << QVector3D( it->x() - this->translate, it->y(), it->z());
        else
            vtx << QVector3D( it->x(), it->y(), it->z());
    }
    this->vertices.clear();
    this->vertices = vtx;*/

}

void Square::moveRight(int w)
{
    int m = this->position.x() + this->translate;
    //qDebug() << "m = " << this->position.x() << " + " << this->translate << " ->" << m;
    if(m < w/2)
    {
        this->rePosition( m, this->position.y() );
    }

    /*if(this->translate + 30 <= w/2)
    {
        this->translate = this->translate + 30;
    }*/

    //this->draw();

    /*QVector<QVector3D> vtx;
    QVector<QVector3D>::iterator it;
    for(it = this->vertices.begin(); it != this->vertices.end(); ++it)
    {
        if(it->x() < +w/2 - 40)
            vtx << QVector3D( it->x() + this->translate, it->y(), it->z());
        else
            vtx << QVector3D( it->x(), it->y(), it->z());
    }
    this->vertices.clear();
    this->vertices = vtx;
    // Atualiza a posição do player
    this->_x = (this->vertices.at(1).x() - this->vertices.at(0).x()) / 2;
    this->_y = (this->vertices.at(2).y() - this->vertices.at(1).y()) / 2;*/
}

bool Square::move()
{
    return false;
}
