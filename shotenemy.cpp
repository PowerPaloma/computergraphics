#include "shotenemy.h"
#include <QtOpenGL>
#include <GL/glu.h>
#include <QTimer>

//TiroPlayer::TiroPlayer(double *v1, double *v2, double *v3, double *v4)
ShotEnemy::ShotEnemy(int x, int y, int screenHeight)
{
    this->nome = "Tiro do inimigo";

    this->translate = 30.0;
    this->position = QVector3D(x, y, 0); // posição inicial do player
    this->width = 10;
    this->height = 30;
    this->screenHeight = screenHeight;

    // Criar os vértices
    this->vertices << QVector3D(this->position.x() - this->width/2, this->position.y() - this->height/2, 0.0) \
            << QVector3D(this->position.x() + this->width/2, this->position.y() - this->height/2, 0.0) \
            << QVector3D(this->position.x() + this->width/2, this->position.y() + this->height/2, 0.0) \
            << QVector3D(this->position.x() - this->width/2, this->position.y() + this->height/2, 0.0);
}

void ShotEnemy::draw()
{
   // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glLoadIdentity();
    glColor3f(0.0,0.0,1.0);

    //glPushMatrix();
    //glTranslatef(0.0, this->translate, 0.0);

    glBegin(GL_QUADS);
    glVertex3d(this->vertices.at(0).x(), this->vertices.at(0).y(), this->vertices.at(0).z());
    glVertex3d(this->vertices.at(1).x(), this->vertices.at(1).y(), this->vertices.at(1).z());
    glVertex3d(this->vertices.at(2).x(), this->vertices.at(2).y(), this->vertices.at(2).z());
    glVertex3d(this->vertices.at(3).x(), this->vertices.at(3).y(), this->vertices.at(3).z());
    glEnd();
    //glPopMatrix();
    this->move();

}

 bool ShotEnemy::move(){
    // Copiando os vértices, já que não dá para alterá-los por serem const
    //qDebug() << "MOVE SHOT ENEMY";
     bool retorno = false;
     QVector<QVector3D> vtx;
     foreach (QVector3D f, this->vertices){
         if(f.y() - this->translate >= this->screenHeight){
             vtx << QVector3D( f.x(), f.y() - this->translate, f.z());
         }else
         {
             retorno = true;
         }

     }
    this->vertices.clear();
    this->vertices = vtx;
    return retorno;

}
