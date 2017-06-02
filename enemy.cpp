#include "enemy.h"
#include "shotenemy.h"
#include <iostream>
#include <QtOpenGL>
#include <GL/glu.h>
#include <QDebug>
#include<QTimer>


//Square::Square(double *v1, double *v2, double *v3, double *v4)
Enemy::Enemy(int x, int y, int w, int h, int widthWind, GLWidget *widget )
{
    this->nome = "Inimigo";

    this->translate = 15.0;
    this->position= QVector3D(x, y, 0); // posição inicial do player
    this->width = w;
    this->height = h;
    this->heightWind= y;
    this->widthWind=widthWind;
    this->widget = widget;
    this->r = (rand() % 101);
    this->g = (rand() % 101);
    this->b = (rand() % 101);

    // Criar os vértices
    this->vertices << QVector3D(this->position.x() - this->width/2, this->position.y() - this->height/2, 0.0) \
            << QVector3D(this->position.x() + this->width/2, this->position.y() - this->height/2, 0.0) \
            << QVector3D(this->position.x() + this->width/2, this->position.y() + this->height/2, 0.0) \
            << QVector3D(this->position.x() - this->width/2, this->position.y() + this->height/2, 0.0);
}

int Enemy::x()
{
    return this->position.x();
}

int Enemy::y()
{
    return this->position.y();
}

void Enemy::draw()
{
    glColor3f(1.0, 0.0, 0.0);

    glPopMatrix();
    glBegin(GL_QUADS);
    glVertex3d(this->vertices.at(0).x(), this->vertices.at(0).y(), this->vertices.at(0).z());
    glVertex3d(this->vertices.at(1).x(), this->vertices.at(1).y(), this->vertices.at(1).z());
    glVertex3d(this->vertices.at(2).x(), this->vertices.at(2).y(), this->vertices.at(2).z());
    glVertex3d(this->vertices.at(3).x(), this->vertices.at(3).y(), this->vertices.at(3).z());
    glEnd();
    glPushMatrix();

    this->move();

}

void Enemy::rePosition(int x, int y)
{
    this->position.setX(x);
    this->position.setY(y);
    this->vertices.clear();
    this->vertices << QVector3D(this->position.x() - this->width/2, this->position.y() - this->height/2, 0.0) \
            << QVector3D(this->position.x() + this->width/2, this->position.y() - this->height/2, 0.0) \
            << QVector3D(this->position.x() + this->width/2, this->position.y() + this->height/2, 0.0) \
            << QVector3D(this->position.x() - this->width/2, this->position.y() + this->height/2, 0.0)  ;
}

bool Enemy::move()
{

    srand(time(NULL));
    int veri = rand() %100;
    bool retorno = false;


    if(veri<=50){
        int aux = this->position.y() -5;
        if(aux >= -this->heightWind)
        {
            //qDebug()<<"auxIf"<<aux;
            this->rePosition(this->position.x(), aux);
        }else{
            //qDebug()<<"auxElse"<<aux;
            retorno = true;
        }
        int m = this->position.x() - this->translate;
        if(m >= -this->widthWind + 20)
        {
            this->rePosition(m, this->position.y());     
        }

    }else{
        int aux = this->position.y() -5;
        if(aux >= -this->heightWind)
        {
            //qDebug()<<"auxIf"<<aux;
            this->rePosition(this->position.x(), aux);
        }else{
            //qDebug()<<"auxElse"<<aux;
            retorno = true;
        }
        int m = this->position.x() + this->translate;
        //qDebug() << "m = " << this->position.x() << " - " << this->translate << " ->" << m;
        if(m <= this->widthWind - 20)
        {
           this->rePosition(m, this->position.y());

        }

    }
      return retorno;




}


