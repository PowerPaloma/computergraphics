#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QtOpenGL/QGLWidget>



class Figure;

class QShortcut;

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);
    ~GLWidget();
    QSize sizeHint() const;
    QList<Figure*> scene;
    QList<Figure*>::iterator it;
    QShortcut *left;
    QShortcut *right;
    QShortcut *space;
    void paintGL();
    bool endGame;

private:
    QShortcut *esc;
    QShortcut *altEnter;

protected:
    void initializeGL();
    //void paintGL();
    void resizeGL(int w, int h);
    void updateGL();
    void testeColisao();

signals:

public slots:
    void toFullScreen();
    void moveLeft();
    void moveRight();
    void shoot();
    void updateMe();


};

#endif // GLWIDGET_H

