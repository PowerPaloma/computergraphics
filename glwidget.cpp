#include "glwidget.h"
#include "player.h"
#include "enemy.h"
#include "shotenemy.h"
#include "tiroplayer.h"
#include <iostream>
#include <QShortcut>
#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer), parent)
{
    // Configura a janela
    this->setMinimumSize(500, 500); // tamanho mínimo
    const QRect screen = QApplication::desktop()->screenGeometry(); // Qual o tamanho do desktop?
    this->move(screen.center() - this->rect().center()); // move a janela para o centro do desktop

    // Configurando atalhos
    this->esc = new QShortcut(Qt::Key_Escape, this); // tecla de escape (para sair do modo FULL SCREEN
    this->altEnter = new QShortcut(Qt::Key_F11, this); // para alternar o modo normal e FULL SCREEN
    this->left = new QShortcut(Qt::Key_Left, this);
    this->right = new QShortcut(Qt::Key_Right, this);
    this->space = new  QShortcut(Qt::Key_Space, this);

    // Faz as conexões necessárias com os SLOTS da classe
    connect(this->esc,SIGNAL(activated()), this, SLOT(showNormal()));
    connect(this->altEnter,SIGNAL(activated()), this, SLOT(toFullScreen()));
    //connect(this->left,SIGNAL(activated()), this, SLOT(moveLeft()));
    //connect(this->right,SIGNAL(activated()), this, SLOT(moveRight()));
    //connect(this->space,SIGNAL(activated()), this, SLOT(shoot()));

    this->endGame = false;
}

GLWidget::~GLWidget()
{
}

void GLWidget::updateMe()
{
    //this->updateGL();
    this->paintGL();
}

// Determina o tamano da janela, quando é mostrada em modo Normal
QSize GLWidget::sizeHint() const
{
    return QSize(500, 500);
}

// Configura a OpenGL
void GLWidget::initializeGL()
{
    glEnable(GL_DOUBLEBUFFER);
    glEnable(GL_DEPTH_TEST);

    // Cor de fundo
    glClearColor(0.0,0.0,0.0,1.0);

    // Determina o quanto da GLWidget será utilizada (para o total)
    glViewport(0,0,this->width(),this->height());

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Mantém a proporção
    glOrtho(-this->width()/2,this->width()/2,-this->height()/2,this->height()/2, 10, -10);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Desenha a cena na tela
void GLWidget::paintGL()
{
    if(this->endGame == false){
        // Limpa os buffers de cor e profundidade
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        qDebug() << "Temos " << this->scene.size() << "na cena";       
        foreach (Figure* f, this->scene)
        {
            f->draw();

            if(f->move())
            {
                qDebug() << "f estah na cena? " <<  this->scene.contains(f);
                qDebug() << "removendo o " << f->nome;
                bool rem = this->scene.removeOne(f);
                if(rem){
                    qDebug() << "Temos " << this->scene.size() << "na cena!";
                }
            }
            //this->testeColisao();
        }

        swapBuffers();
    }else{
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        return;
    }
}

// Atualiza as configurações da OpenGL sempre que necessário
void GLWidget::updateGL()
{
    glViewport(0,0,this->width(),this->height());
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Mantém a proporção
    glOrtho(-this->width()/2,this->width()/2,-this->height()/2,this->height()/2, 10, -10);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Requisita uma atualização da GLWidget caso a janela seja redimensionada
void GLWidget::resizeGL(int w, int h)
{
    qDebug() <<"RES: " << w << " x " << h ;
    this->updateGL();
}
/*
void GLWidget::testeColisao()
{
    Figure *obj;
    Figure *obj2;

    foreach (obj, this->scene)
    {
        foreach (obj2, this->scene)
        {
            if(((obj->vertices.at(0).x() < obj2->vertices.at(2).x() && obj->vertices.at(0).x() > obj2->vertices.at(0).x()) || (obj->vertices.at(2).x() < obj2->vertices.at(2).x() && obj->vertices.at(2).x() > obj2->vertices.at(0).x())) && ((obj->vertices.at(0).y() < obj2->vertices.at(2).y() && obj->vertices.at(0).y() > obj2->vertices.at(0).y()) || (obj->vertices.at(2).y() < obj2->vertices.at(2).y() && obj->vertices.at(2).y() > obj2->vertices.at(0).y())))
            {
                //qDebug() << "COLIDIU";

                if(dynamic_cast<Enemy*>(obj) && dynamic_cast<Square*>(obj2)) //inimigo com player
                {
                    this->scene.removeOne(obj); this->scene.removeOne(obj2);
                    this->endGame = true;
                    //qDebug() << "remove obj e obj2. FIM JOGO";
                    //qDebug() << "inimigo com player";
                }

                if(dynamic_cast<Enemy*>(obj2) && dynamic_cast<Square*>(obj)) //inimigo com player
                {
                    this->scene.removeOne(obj); this->scene.removeOne(obj2);
                    this->endGame = true;
                    //qDebug() << "remove obj e obj2. FIM JOGO";
                    //qDebug() << "inimigo com player";
                }

                if(dynamic_cast<ShotEnemy*>(obj) && dynamic_cast<Square*>(obj2)) //tiro inimigo e player
                {
                    this->scene.removeOne(obj); this->scene.removeOne(obj2);
                    this->endGame = true;
                    //qDebug() << "remove obj e obj2. FIM JOGO";
                    //qDebug() << "tiro inimigo e player";
                    //this->scene.removeOne(obj); this->scene.removeOne(obj2);
                }

                if(dynamic_cast<ShotEnemy*>(obj2) && dynamic_cast<Square*>(obj)) //tiro inimigo e player
                {
                    this->scene.removeOne(obj); this->scene.removeOne(obj2);
                    this->endGame = true;
                    //qDebug() << "remove obj e obj2. FIM JOGO";
                    //qDebug() << "tiro inimigo e player";
                }

                if(dynamic_cast<TiroPlayer*>(obj) && dynamic_cast<Enemy*>(obj2)) //tiro player e inimigo
                {
                    this->scene.removeOne(obj); this->scene.removeOne(obj2);
                    //qDebug() << "remove obj e obj2.";
                    //qDebug() << "tiro player e inimigo";
                }

                if(dynamic_cast<TiroPlayer*>(obj2) && dynamic_cast<Enemy*>(obj)) //tiro player e inimigo
                {
                    this->scene.removeOne(obj); this->scene.removeOne(obj2);
                    //qDebug() << "remove obj e obj2.";
                    //qDebug() << "tiro player e inimigo";
                }

            }

        }
    }
}*/

// Alterna os modos tela cheia e normal
void GLWidget::toFullScreen()
{
    if (this->windowState() != Qt::WindowFullScreen)
        this->setWindowState(Qt::WindowFullScreen);
    else
    {
        const QRect screen = QApplication::desktop()->screenGeometry();
        this->move(screen.center() - this->rect().center());
        this->showNormal();
    }
}

void GLWidget::moveLeft()
{
    //this->isLeft = true;
}

void GLWidget::moveRight()
{
    //this->isLeft = false;
}

void GLWidget::shoot()
{
    //this->isLeft = false;
}

