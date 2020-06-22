#ifndef BULLET_H
#define BULLET_H
#include <qpoint.h>
#include <qpropertyanimation.h>
#include <enemy.h>
#include <mainwindow.h>
#include <qsize.h>
class MainWindow;
class Enemy;
class Bullet:public QObject
{
    Q_OBJECT
    Q_PROPERTY(QPoint m_currentPos READ currentPos WRITE setCurrentPos)
public:
    Bullet(QPoint startPos,QPoint targetPos,int damage
                   ,Enemy* target,MainWindow *game,int type,
                   const QPixmap& sprite = QPixmap(":/Resources/bullet.png"));
    void draw(QPainter *painter) const;
    void move();
    void setCurrentPos(QPoint pos);
    QPoint currentPos(){return m_currentPos;}
public slots:
    void hitTarget();
private:
    QPoint m_currentPos;
    const QPoint m_startPos;
    const QPoint m_targetPos;
    QPixmap m_sprite;
    Enemy* m_target;
    MainWindow* m_game;
    int m_damage;
    static const QSize m_size;
    int m_type;
};

#endif // BULLET_H
