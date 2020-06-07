#ifndef ENEMY_H
#define ENEMY_H
#include <qpoint.h>
#include <qpixmap.h>
#include <waypoint.h>
#include <mainwindow.h>
#include <qobject.h>
#include <qsize.h>
#include <qpainter.h>
class WayPoint;
class QPainter;
class MainWindow;
class Tower;

class Enemy:public QObject
{
    Q_OBJECT
public:
    Enemy(Waypoint *startWayPoint, MainWindow *game, const QPixmap &sprite=QPixmap(":/Resources/enemy.jpg"));
    void draw(QPainter *painter);
    void move();
public slots:
    void doActivate();
protected:
    int m_maxHP;
    int m_currentHP;
    double m_speed;
    bool m_active;
    QPoint m_pos;
    QPixmap m_sprite;
    Waypoint* m_destinationWayPoint;
    MainWindow* m_game;
    double m_rotationSprite;
    QSize ms_fixedSize;
};
#endif // ENEMY_H
