#ifndef ENEMY_H
#define ENEMY_H
#include <qpoint.h>
#include <qpixmap.h>
#include <waypoint.h>
#include <mainwindow.h>
#include <qobject.h>
#include <qsize.h>
#include <qpainter.h>
#include <qlist.h>
class WayPoint;
class QPainter;
class MainWindow;
class Tower;

class Enemy:public QObject
{
    Q_OBJECT
public:
    Enemy(Waypoint *startWayPoint, MainWindow *game, const QPixmap &sprite=QPixmap(":/Resources/enemy.png"));
    ~Enemy();
    void draw(QPainter *painter);
    void move();
    QPoint pos();
    void getRemoved();
    void getDamaged(int damage);
    void getAttacked(Tower* attacker);
    void gotLostSight(Tower* attacker);
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
    QList<Tower*> m_attackedTowersList;
};
#endif // ENEMY_H
