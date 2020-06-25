#include "enemy.h"
#include "waypoint.h"
#include "tower.h"
#include "utility.h"
#include "mainwindow.h"
#include <math.h>
#include <QPainter>
#include <QColor>
#include <QDebug>
#include <QMatrix>
#include <QVector2D>
#include <QtMath>

Enemy::Enemy(Waypoint *startWayPoint, MainWindow *game, int waves ,const QPixmap &sprite)
    :QObject(0)
    ,m_pos(startWayPoint->pos())
    ,m_sprite(sprite)
    ,m_destinationWayPoint(startWayPoint->nextWayPoint())
    ,ms_fixedSize(60,40)
    ,m_waves(waves)
{
     m_maxHP = 20+10*m_waves;
     m_currentHP = 20+10*m_waves;
     m_active= false;
     m_speed = 1+0.1*m_waves;
     m_rotationSprite=0.0;
     m_game = game;
};
Enemy::~Enemy()
{
    m_attackedTowersList.clear();
    m_destinationWayPoint = NULL;
    m_game = NULL;
}
void Enemy::gotLostSight(Tower *attacker)
{
    m_attackedTowersList.removeOne(attacker);
}
void Enemy::draw(QPainter *painter)
{
    if(!m_active)
        return;
    static const int Health_Bar_Width = 20;
    painter->save();
    QPoint healthBarPoint = m_pos + QPoint(-Health_Bar_Width/2-5,-ms_fixedSize.height()/3);
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    QRect healthBarBackRect(healthBarPoint,QSize((double)m_currentHP/m_maxHP * Health_Bar_Width,2));
    painter->drawRect(healthBarBackRect);
    painter->setBrush(Qt::green);
    QRect healthBarRect(healthBarPoint, QSize((double)m_currentHP / m_maxHP * Health_Bar_Width, 2));
    painter->drawRect(healthBarRect);
    static const QPoint offsetPoint(-ms_fixedSize.width()/2,-ms_fixedSize.height()/2);
    painter->translate(m_pos);
    painter->rotate(m_rotationSprite);
    painter->drawPixmap(offsetPoint,QPixmap(":/Resources/enemy.png"));
    painter->restore();
}
QPoint Enemy::pos(){return m_pos;}
void Enemy::move()
{
    if (!m_active)
        return;

    if (collisionWithCircle(m_pos, 1, m_destinationWayPoint->pos(), 1))
    {
        if (m_destinationWayPoint->nextWayPoint())
        {
            m_pos = m_destinationWayPoint->pos();
            m_destinationWayPoint = m_destinationWayPoint->nextWayPoint();
        }
        else
        {
            m_game->getHpDamage();
            m_game->removedEnemy(this);
            return;
        }
    }

    QPoint targetPoint = m_destinationWayPoint->pos();
    QPoint offsetPoint = (targetPoint-m_pos);
    if(offsetPoint.x()==0)
    {
    m_pos = m_pos + QPoint(0,1)*2*m_speed;}
    else if(offsetPoint.x()>0){
    m_pos = m_pos + QPoint(1,0)*2*m_speed;
}
    else {
    m_pos = m_pos + QPoint(-1,0)*2*m_speed;
    }

}
void Enemy::doActivate()
{
    m_active = true;

}
void Enemy::getAttacked(Tower *attacker)
{
    m_attackedTowersList.push_back(attacker);
}
void Enemy::getRemoved()
{
    if(m_attackedTowersList.empty())
        return;
    foreach(Tower* attacker,m_attackedTowersList)
        attacker->targetkilled();
    m_game->removedEnemy(this);
}
void Enemy::getDamaged(int damage)
{
    m_currentHP-=damage;
    if(m_currentHP<=1)
        {
        m_game->awardGold(100);
        this->getRemoved();
        }
}
void Enemy::slowdown()
{
    if(isSlowedDown==false)
    {
        isSlowedDown=true;
        m_speed*=0.5;
    }

}
