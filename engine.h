#ifndef ENGINE_H
#define ENGINE_H

#include <QtOpenGL/QGLWidget>
#include "glwidget.h"
#include "player.h"
#include"tiroplayer.h"

class QShortcut;

class Engine : public QObject
{
    Q_OBJECT

public:
    explicit Engine(GLWidget *gw);
    ~Engine();
    void createPlayer();
    void createShot();
    void mover();

    //void createEnemy();

private:
    GLWidget  *w;
    Square    *player;
    TiroPlayer *shot;
    QShortcut *left;
    QShortcut *right;

signals:
    void update();

    //void createShotEnemy(int x, int y, int w);


public slots:
    void testeColisao();
    void createEnemy();
    void moveLeft();
    void moveRight();
    void shoot();
    //void enemy();
    //void createShotEnemy();

};

#endif // ENGINE_H
