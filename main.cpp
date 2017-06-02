#include "glwidget.h"
#include "engine.h"
#include <QApplication>

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    GLWidget *gw = new GLWidget;
    Engine eng(gw);
    eng.createPlayer();
    eng.createEnemy();

    return app.exec();
}
