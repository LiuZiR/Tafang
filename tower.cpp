#include "tower.h"
#include "mainwindow.h"
#include <enemy.h>
#include <bullet.h>
#include <qpixmap.h>
#include <qpainter.h>
#include <qsize.h>
#include <QColor>
#include <QTimer>
#include <QVector2D>
#include <QtMath>
#include <utility.h>
const QSize Tower::Size(44, 44);

Tower::Tower(QPoint pos,MainWindow* game,const QPixmap &sprite)
: m_damage(10)
, m_firerate(1000)
, m_rotationSprite(-45.0)
, m_chooseEnemy(NULL)
, m_game(game)
, m_pos(pos)
, m_sprite(sprite)
, m_type(0)
{
  m_attackRange=120;
  m_fireRateTimer = new QTimer(this);
  connect(m_fireRateTimer, SIGNAL(timeout()), this, SLOT(shootWeapon()));
}
void Tower::checkEnemyinRange()
{
    if(m_chooseEnemy)
    {
        QVector2D normalized(m_chooseEnemy->pos() - m_pos);
        normalized.normalize();
        m_rotationSprite = qRadiansToDegrees(qAtan2(normalized.y(), normalized.x()))+45.0;
        if(!collisionWithCircle(m_pos,m_attackRange,m_chooseEnemy->pos(),1))
            looseSightofEnemy();
    }
    else {
        QList<Enemy *> enemyList = m_game->enemyList();
        foreach(Enemy *enemy,enemyList)
            if(collisionWithCircle(m_pos,m_attackRange,enemy->pos(),1))
               { chooseEnemyforAttack(enemy);
                 break;}
    }
}
void Tower::attackEnemy()
{
    m_fireRateTimer->start(m_firerate);
}
void Tower::chooseEnemyforAttack(Enemy* enemy)
{
    m_chooseEnemy=enemy;
    attackEnemy();
    m_chooseEnemy->getAttacked(this);
}
void Tower::shootWeapon()
{
    Bullet *bullet = new Bullet(m_pos,m_chooseEnemy->pos(),m_damage,m_chooseEnemy,m_game,m_type);
    bullet->move();
    m_game->addBullet(bullet);
}
void Tower::targetkilled()
{
    if(m_chooseEnemy)
    {m_chooseEnemy=NULL;}
    m_fireRateTimer->stop();
    m_rotationSprite=0.0;
}
void Tower::looseSightofEnemy()
{
    m_chooseEnemy->gotLostSight(this);
    if(m_chooseEnemy)
        m_chooseEnemy=NULL;
    m_fireRateTimer->stop();
    m_rotationSprite=0.0;
}
void Tower::draw_range(QPainter *painter)
{
    if(m_type==1)
    m_sprite = QPixmap(":/Resources/bottle.png");
    painter->save();
    painter->setPen(Qt::white);

    static const QPoint offsetPoint(-Size.width()/2,-Size.height()/2);
    painter->translate(m_pos);
    painter->rotate(m_rotationSprite);
    painter->drawPixmap(offsetPoint,m_sprite);
    painter->restore();
}
