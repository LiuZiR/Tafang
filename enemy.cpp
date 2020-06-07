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

Enemy::Enemy(Waypoint *startWayPoint, MainWindow *game, const QPixmap &sprite)
    :QObject(0)
    ,m_pos(startWayPoint->pos())
    ,m_sprite(sprite)
    ,m_destinationWayPoint(startWayPoint->nextWayPoint()),
     ms_fixedSize(60,40)
{
     m_maxHP = 40;
     m_currentHP = 40;
     m_active= false;
     m_speed = 0.1;
     m_rotationSprite=0.0;
     m_game = game;
};

void Enemy::draw(QPainter *painter)
{
    if(!m_active)
        return;
    static const int Health_Bar_Width = 20;
    painter->save();
    QPoint healthBarPoint = m_pos + QPoint(-Health_Bar_Width/2-5,-ms_fixedSize.height()/3);
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    QRect healthBarBackRect(healthBarPoint,QSize((double)m_currentHP/m_maxHP*Health_Bar_Width,2));
    painter->drawRect(healthBarBackRect);
    static const QPoint offsetPoint(-ms_fixedSize.width()/2,-ms_fixedSize.height()/2);
    painter->translate(m_pos);
    painter->rotate(m_rotationSprite);
    painter->drawPixmap(offsetPoint,m_sprite);
    painter->restore();
}
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
    m_pos = m_pos + QPoint(0,1)*2;}
    else if(offsetPoint.x()>0){
    m_pos = m_pos + QPoint(1,0)*2;
}
    else {
    m_pos = m_pos + QPoint(-1,0)*2;
    }
    /*
    qreal movementSpeed = m_speed;
    QVector2D normalized(targetPoint - m_pos);
    normalized.normalize();
    m_pos = m_pos + normalized.toPoint() * movementSpeed;
    m_rotationSprite = qRadiansToDegrees(qAtan2(normalized.y(), normalized.x())) + 180;*/
}
void Enemy::doActivate()
{
    m_active = true;
}
