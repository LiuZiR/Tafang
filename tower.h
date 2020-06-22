#ifndef TOWER_H
#define TOWER_H
#include <qpoint.h>
#include <qpixmap.h>
#include <enemy.h>
#include <mainwindow.h>
class Enemy;
class MainWindow;
class Tower:public QObject
{
    Q_OBJECT
public:
    Tower(QPoint pos,MainWindow* game,const QPixmap &sprite=QPixmap(":/Resources/greenBottle.png"));
    void draw_range(QPainter *painter);
    void targetkilled();
    void attackEnemy();
    void chooseEnemyforAttack(Enemy* enemy);
    void removeBullet();
    void looseSightofEnemy();
    void checkEnemyinRange();
    void setType(int type){m_type=type;}
public slots:
    void shootWeapon();
protected:
    static const QSize Size;
    QPoint m_pos;
    int m_attackRange;
    int m_damage;
    int m_firerate;
    QPixmap  m_sprite;
    double m_rotationSprite;
    Enemy* m_chooseEnemy;
    QTimer* m_fireRateTimer;
    MainWindow* m_game;
    int m_type;
};

#endif // TOWER_H
