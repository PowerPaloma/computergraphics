#include "engine.h"
#include "player.h"
#include"enemy.h"
#include"shotenemy.h"
#include <QShortcut>
#include <iostream>
#include <QtOpenGL>
#include <GL/glu.h>
#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>
#include <QTimer>
#include <stdlib.h>

Engine::Engine(GLWidget *gw)
{
    this->w = gw;
    this->w->show();

    // Faz as conexões necessárias com os SLOTS da classe
    connect(this->w->left,SIGNAL(activated()), this, SLOT(moveLeft()));
    connect(this->w->right,SIGNAL(activated()), this, SLOT(moveRight()));
    connect(this->w->space,SIGNAL(activated()), this, SLOT(shoot()));
    connect(this, SIGNAL(update()), this->w, SLOT(updateMe()));

    QTimer *timer = new QTimer(this);
    timer->start(95);
    connect(timer, SIGNAL(timeout()), this->w, SLOT(update()));

    QTimer *timer_enemy = new QTimer(this);
    timer_enemy->start(2000);
    connect(timer_enemy, SIGNAL(timeout()), this, SLOT(createEnemy()));

    QTimer *timer_colisao = new QTimer(this);
    timer_colisao->start(95);
    connect(timer_colisao, SIGNAL(timeout()), this, SLOT(testeColisao()));

    /*QTimer *timer_shotEnemy = new QTimer(this);
    timer_shotEnemy->start(2000);
    connect(timer_shotEnemy, SIGNAL(timeout()), this, SLOT(createShotEnemy()));*/



}

Engine::~Engine(){
    delete this->w;
}

void Engine::createPlayer()
{

    int w = 40; // Largura do player
    int h = 30; // Altura do player
    this->player = new Square(0, -this->w->height()/2 + h/2, w, h );
    // Adiciona um quadrado à cena (Polimorfismo)
    this->w->scene.append(this->player);
}
void Engine::createShot()
{

    //qDebug() << "Tiro em:"   << this->player->x() << ", " << this->player->y() << "," << this->w->height();
    Figure *shot = new TiroPlayer( this->player->x(), this->player->y(), this->w->height());
    this->w->scene.append(shot);

}



void Engine::createEnemy()
{

    srand(time(NULL));
    int posX= (-this->w->width()/2) + 20 + rand()%this->w->width()/2 - 20; //qDebug() << "posX: " << posX;
    int w = 40; // Largura do player
    int h = 30; // Altura do player
    Figure *enemy = new Enemy(posX, this->w->height()/2, w, h, this->w->width()/2, this->w);
    // Adiciona um quadrado à cena (Polimorfismo)
    this->w->scene.append(enemy);

    //Figure *shot = new ShotEnemy(posX, this->w->height()/2, -this->w->height()/2, this->w);
    //this->w->scene.append(shot);



}


void Engine::moveLeft()
{

    this->player->moveLeft(this->w->width());
    //this->w->update();
}

void Engine::moveRight()
{

    this->player->moveRight(this->w->width());
    //this->w->update();
}

void Engine::shoot()
{
   this->createShot();
}

void Engine::testeColisao()
{
    Figure *obj;
    Figure *obj2;

    foreach (obj, this->w->scene)
    {
        foreach (obj2, this->w->scene)
        {
            if(((obj->vertices.at(0).x() < obj2->vertices.at(2).x() && obj->vertices.at(0).x() > obj2->vertices.at(0).x()) || (obj->vertices.at(2).x() < obj2->vertices.at(2).x() && obj->vertices.at(2).x() > obj2->vertices.at(0).x())) && ((obj->vertices.at(0).y() < obj2->vertices.at(2).y() && obj->vertices.at(0).y() > obj2->vertices.at(0).y()) || (obj->vertices.at(2).y() < obj2->vertices.at(2).y() && obj->vertices.at(2).y() > obj2->vertices.at(0).y())))
            {
                //qDebug() << "COLIDIU";

                if(dynamic_cast<Enemy*>(obj) && dynamic_cast<Square*>(obj2)) //inimigo com player
                {
                    this->player->life -= 1;
                    //qDebug() << "vidas1"<<this->player->life;
                    if(this->player->life == 0){
                        this->w->scene.removeOne(obj); this->w->scene.removeOne(obj2);
                        this->w->endGame = true;
                    }

                    //qDebug() << "remove obj e obj2. FIM JOGO";
                    //qDebug() << "inimigo com player";
                }

                if(dynamic_cast<ShotEnemy*>(obj) && dynamic_cast<Square*>(obj2)) //tiro inimigo e player
                {
                    this->player->life -= 1;
                    //qDebug() << "vidas"<<this->player->life;
                    if(this->player->life == 0){
                        this->w->scene.removeOne(obj); this->w->scene.removeOne(obj2);
                        this->w->endGame = true;
                    }
                    //qDebug() << "remove obj e obj2. FIM JOGO";
                    //qDebug() << "tiro inimigo e player";
                    //this->scene.removeOne(obj); this->scene.removeOne(obj2);
                }


                if(dynamic_cast<TiroPlayer*>(obj) && dynamic_cast<Enemy*>(obj2)) //tiro player e inimigo
                {

                    this->w->scene.removeOne(obj); this->w->scene.removeOne(obj2);
                    //qDebug() << "remove obj e obj2.";
                    //qDebug() << "tiro player e inimigo";
                }


            }

        }
    }
}


